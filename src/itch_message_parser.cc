#include <cstdint>

#include <itch_parser.hh>
#include <itch_buffer.hh>
#include <itch_message_types.hh>

#include <endian_conversion.hh>

namespace {
  std::uint32_t convert_uint32(unsigned char const *pos) {
    return Itch4::network_to_host_32(*reinterpret_cast<std::uint32_t const*>(pos));
  }

  std::uint64_t convert_uint64(unsigned char const *pos) {
    return Itch4::network_to_host_64(*reinterpret_cast<std::uint64_t const*>(pos));
  }
}  

namespace Itch4 {
  Parser_state parse_add_order_no_mpid_message(Buffer const &buffer, Message &message) {
    Add_order_no_mpid_message &msg = message.message_types.add_order_no_mpid_message;

    msg.nanoseconds = convert_uint32(&buffer[1]);
    msg.order_reference_number = convert_uint64(&buffer[5]);
    msg.buy_sell_indicator = static_cast<Buy_sell_indicator>(buffer[13]);
    msg.shares = convert_uint32(&buffer[14]);
    msg.stock_symbol.assign(&buffer[18], &buffer[18 + 8]);
    msg.price = convert_uint32(&buffer[26]);
    
    return PS_SUCCESS;
  }
  
  Parser_state parse_broken_trade_message(Buffer const &buffer, Message &message) {
    Broken_trade_message &msg = message.message_types.broken_trade_message;

    msg.nanoseconds = convert_uint32(&buffer[1]);
    msg.match_number = convert_uint64(&buffer[5]);
    
    return PS_SUCCESS;
  }
  
  Parser_state parse_order_executed_with_price_message(Buffer const &buffer, Message &message) {
    Order_executed_with_price_message &msg = message.message_types.order_executed_with_price_message;

    msg.nanoseconds = convert_uint32(&buffer[1]);
    msg.order_reference_number = convert_uint64(&buffer[5]);
    msg.executed_shares = convert_uint32(&buffer[13]);
    msg.match_number = convert_uint64(&buffer[17]);    
    msg.printable = static_cast<Printable>(buffer[25]);
    msg.execution_price = convert_uint32(&buffer[26]);
    
    return PS_SUCCESS;
  }
  
  Parser_state parse_order_delete_message(Buffer const &buffer, Message &message) {
    Order_delete_message &msg = message.message_types.order_delete_message;

    msg.nanoseconds = convert_uint32(&buffer[1]);
    msg.order_reference_number = convert_uint64(&buffer[5]);
    
    return PS_SUCCESS;
  }
  
  Parser_state parse_order_executed_message(Buffer const &buffer, Message &message) {
    Order_executed_message &msg = message.message_types.order_executed_message;

    msg.nanoseconds = convert_uint32(&buffer[1]);
    msg.order_reference_number = convert_uint64(&buffer[5]);
    msg.executed_shares = convert_uint32(&buffer[13]);
    msg.match_number = convert_uint64(&buffer[17]);
    
    return PS_SUCCESS;
  }
  
  Parser_state parse_add_order_with_mpid_message(Buffer const &buffer, Message &message) {
    Add_order_with_mpid_message &msg = message.message_types.add_order_with_mpid_message;

    msg.nanoseconds = convert_uint32(&buffer[1]);
    msg.order_reference_number = convert_uint64(&buffer[5]);
    msg.buy_sell_indicator = static_cast<Buy_sell_indicator>(buffer[13]);
    msg.shares = convert_uint32(&buffer[14]);
    msg.stock_symbol.assign(&buffer[18], &buffer[18 + 8]);
    msg.price = convert_uint32(&buffer[26]);
    msg.attribution.assign(&buffer[30], &buffer[30 + 4]);
    
    return PS_SUCCESS;
  }
  
  Parser_state parse_stock_trading_action_message(Buffer const &buffer, Message &message) {
    Stock_trading_action_message &msg = message.message_types.stock_trading_action_message;

    msg.nanoseconds = convert_uint32(&buffer[1]);
    msg.stock_symbol.assign(&buffer[5], &buffer[5 + 8]);
    msg.trading_state = static_cast<Trading_state>(buffer[13]);
    /* This message has a reserved item, ignoring */
    msg.reason.assign(&buffer[15], &buffer[15 + 4]);
    
    return PS_SUCCESS;
  }
  
  Parser_state parse_net_order_imbalance_indicator_message(Buffer const &buffer, Message &message) {
    Net_order_imbalance_indicator_message &msg = message.message_types.net_order_imbalance_indicator_message;

    msg.nanoseconds = convert_uint32(&buffer[1]);
    msg.paired_shares = convert_uint64(&buffer[5]);
    msg.imbalance_shares = convert_uint64(&buffer[13]);
    msg.imbalance_direction = static_cast<Imbalance_direction>(buffer[21]);
    msg.stock_symbol.assign(&buffer[22], &buffer[22 + 8]);
    msg.far_price = convert_uint32(&buffer[30]);
    msg.near_price = convert_uint32(&buffer[34]);
    msg.current_reference_price = convert_uint32(&buffer[38]);
    msg.cross_type = static_cast<Cross_type>(buffer[42]);
    msg.price_variation_indicator = static_cast<Price_variation_indicator>(buffer[43]);
    
    return PS_SUCCESS;
  }
  
  Parser_state parse_market_participant_message(Buffer const &buffer, Message &message) {
    Market_participant_message &msg = message.message_types.market_participant_message;

    msg.nanoseconds = convert_uint32(&buffer[1]);
    msg.mpid.assign(&buffer[5], &buffer[5 + 4]);
    msg.stock_symbol.assign(&buffer[9], &buffer[9 + 8]);
    msg.primary_market_maker = static_cast<Primary_market_maker>(buffer[17]);
    msg.market_maker_mode = static_cast<Market_maker_mode>(buffer[18]);
    msg.market_participant_state = static_cast<Market_participant_state>(buffer[19]);
    
    return PS_SUCCESS;
  }
  
  Parser_state parse_trade_message(Buffer const &buffer, Message &message) {
    Trade_message &msg = message.message_types.trade_message;

    msg.nanoseconds = convert_uint32(&buffer[1]);
    msg.order_reference_number = convert_uint64(&buffer[5]);
    msg.buy_sell_indicator = static_cast<Buy_sell_indicator>(buffer[13]);
    msg.shares = convert_uint32(&buffer[14]);
    msg.stock_symbol.assign(&buffer[18], &buffer[18 + 8]);
    msg.price = convert_uint32(&buffer[26]);
    msg.match_number = convert_uint64(&buffer[30]);
    
    return PS_SUCCESS;
  }
  
  Parser_state parse_cross_trade_message(Buffer const &buffer, Message &message) {
    Cross_trade_message &msg = message.message_types.cross_trade_message;

    msg.nanoseconds = convert_uint32(&buffer[1]);
    msg.shares = convert_uint64(&buffer[5]);
    msg.stock_symbol.assign(&buffer[13], &buffer[13 + 8]);
    msg.cross_price = convert_uint32(&buffer[21]);
    msg.match_number = convert_uint64(&buffer[25]);
    msg.cross_type = static_cast<Cross_type>(buffer[33]);
    
    return PS_SUCCESS;
  }
  
  Parser_state parse_system_directory_message(Buffer const &buffer, Message &message) {
    Stock_directory_message &msg = message.message_types.stock_directory_message;

    msg.nanoseconds = convert_uint32(&buffer[1]);
    msg.stock_symbol.assign(&buffer[5], &buffer[13]);
    msg.market_category = static_cast<Market_category>(buffer[13]);
    msg.financial_status_indicator = static_cast<Financial_status_indicator>(buffer[14]);
    msg.round_lot_size = convert_uint32(&buffer[15]);
    msg.round_lots_only = static_cast<Round_lots_only>(buffer[19]);
    
    return PS_SUCCESS;
  }
  
  Parser_state parse_system_event_message(Buffer const &buffer, Message &message) {
    System_event_message &msg = message.message_types.system_event_message;

    msg.nanoseconds = convert_uint32(&buffer[1]);
    msg.sec = static_cast<System_event_code>(buffer[5]);
    
    return PS_SUCCESS;
  }
  
  Parser_state parse_timestamp_message(Buffer const &buffer, Message &message) {
    Timestamp_message &msg = message.message_types.timestamp_message;
    
    msg.seconds = convert_uint32(&buffer[1]);

    return PS_SUCCESS;
  }
  
  Parser_state parse_order_replace_message(Buffer const &buffer, Message &message) {
    Order_replace_message &msg = message.message_types.order_replace_message;

    msg.nanoseconds = convert_uint32(&buffer[1]);
    msg.original_order_reference_number = convert_uint64(&buffer[5]);
    msg.new_order_reference_number = convert_uint64(&buffer[13]);
    msg.shares = convert_uint32(&buffer[21]);
    msg.price = convert_uint32(&buffer[25]);
    
    return PS_SUCCESS;
  }
  
  Parser_state parse_order_cancel_message(Buffer const &buffer, Message &message) {
    Order_cancel_message &msg = message.message_types.order_cancel_message;

    msg.nanoseconds = convert_uint32(&buffer[1]);
    msg.order_reference_number = convert_uint64(&buffer[5]);
    msg.canceled_shares = convert_uint32(&buffer[13]);
    
    return PS_SUCCESS;
  }
  
  Parser_state parse_reg_sho_message(Buffer const &buffer, Message &message) {
    Reg_sho_message &msg = message.message_types.reg_sho_message;

    msg.nanoseconds = convert_uint32(&buffer[1]);
    msg.stock_symbol.assign(&buffer[5], &buffer[5 + 8]);
    msg.reg_sho_action = static_cast<Reg_sho_action>(buffer[13]);
    
    return PS_SUCCESS;
  }
}
