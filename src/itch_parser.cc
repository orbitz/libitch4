#include <itch_parser.hh>

#include <itch_message_parser.hh>

#include <ascii_table.hh>

namespace {
  unsigned int const INDEX_NOT_FOUND = 26;

  struct Message_entry {
    size_t message_length;
    Itch4::Message_parser message_parser;
  };

  /*
   * We know that the messages coming in are encoding using ASCII
   * so we can use obvious ASCII transformations
   * (nice catch Jon)
   *
   * Returns INDEX_NOT_FOUND on failure
   */
  unsigned int letter_to_index(unsigned int letter) {
    if(letter >= Itch4::ASCII_A && letter <= Itch4::ASCII_Z) {
      return letter - Itch4::ASCII_A;
    }

    return INDEX_NOT_FOUND;
  }
}

namespace Itch4 {

  Parser_state parse_buffer(Buffer &buffer, Message &message) {
    static Message_entry const parsers[26] = {
      {30, parse_add_order_no_mpid_message}, // A
      {13, parse_broken_trade_message}, // B
      {30, parse_order_executed_with_price_message}, // C
      {13, parse_order_delete_message}, // D
      {25, parse_order_executed_message}, // E
      {34, parse_add_order_with_mpid_message}, // F
      {0, 0}, // G
      {19, parse_stock_trading_action_message}, // H
      {44, parse_net_order_imbalance_indicator_message}, // I
      {0, 0}, // J
      {0, 0}, // K
      {20, parse_market_participant_message}, // L
      {0, 0}, // M
      {0, 0}, // N
      {0, 0}, // O
      {38, parse_trade_message}, // P
      {34, parse_cross_trade_message}, // Q
      {20, parse_system_directory_message}, // R
      {6, parse_system_event_message}, // S
      {5, parse_timestamp_message}, // T
      {29, parse_order_replace_message}, // U
      {0, 0}, // V
      {0, 0}, // W
      {17, parse_order_cancel_message}, // X
      {14, parse_reg_sho_message}, // Y
      {0, 0}, // Z
    };

    // Get alpha position
    unsigned int alpha_pos = letter_to_index(buffer[0]);

    if(INDEX_NOT_FOUND == alpha_pos)
        return PS_PARSE_ERROR;

    Message_entry message_entry = parsers[alpha_pos];

    if(buffer.capacity() > 0 && message_entry.message_length <= buffer.capacity())
    {
      message.current_message = static_cast<Message_types>(buffer[0]);
      Parser_state ret = message_entry.message_parser(buffer, message);
      return ret;
    }
    else {
      return PS_NEED_MORE;
    }
  }

  
  Dispatch_error Message::dispatch(Message_switch &message_switch) const {
    switch(message_type()) {
    case MT_TIMESTAMP:
      return message_switch.handle(message_types.timestamp_message);
    case MT_SEM:
      return message_switch.handle(message_types.system_event_message);
    case MT_SDM:
      return message_switch.handle(message_types.stock_directory_message);
    case MT_STAM:
      return message_switch.handle(message_types.stock_trading_action_message);
    case MT_RSSSPTM:
      return message_switch.handle(message_types.reg_sho_message);
    case MT_MPPM:
      return message_switch.handle(message_types.market_participant_message);
    case MT_AONMM:
      return message_switch.handle(message_types.add_order_no_mpid_message);
    case MT_AOWMM:
      return message_switch.handle(message_types.add_order_with_mpid_message);
    case MT_OEM:
      return message_switch.handle(message_types.order_executed_message);
    case MT_OEWPM:
      return message_switch.handle(message_types.order_executed_with_price_message);
    case MT_OCM:
      return message_switch.handle(message_types.order_cancel_message);
    case MT_ODM:
      return message_switch.handle(message_types.order_delete_message);
    case MT_ORM:
      return message_switch.handle(message_types.order_replace_message);
    case MT_TRADEM:
      return message_switch.handle(message_types.trade_message);
    case MT_CROSSTRADEM:
      return message_switch.handle(message_types.cross_trade_message);
    case MT_BROKENTRADEM:
      return message_switch.handle(message_types.broken_trade_message);
    case MT_NOIIM:
      return message_switch.handle(message_types.net_order_imbalance_indicator_message);
    default:
      return D_UNKNOWN_MESSAGE;
    }
  }
}
