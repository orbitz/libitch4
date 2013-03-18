#ifndef ITCH_MESSAGE_PARSER_HH
#define ITCH_MESSAGE_PARSER_HH

#include <itch_parser.hh>

namespace Itch4 {
  typedef Parser_state (*Message_parser)(Buffer const &, Message &);

  Parser_state parse_add_order_no_mpid_message(Buffer const &buffer, Message &message);
  Parser_state parse_broken_trade_message(Buffer const &buffer, Message &message);
  Parser_state parse_order_executed_with_price_message(Buffer const &buffer, Message &message);
  Parser_state parse_order_delete_message(Buffer const &buffer, Message &message);
  Parser_state parse_order_executed_message(Buffer const &buffer, Message &message);
  Parser_state parse_add_order_with_mpid_message(Buffer const &buffer, Message &message);
  Parser_state parse_stock_trading_action_message(Buffer const &buffer, Message &message);
  Parser_state parse_net_order_imbalance_indicator_message(Buffer const &buffer, Message &message);
  Parser_state parse_market_participant_message(Buffer const &buffer, Message &message);
  Parser_state parse_trade_message(Buffer const &buffer, Message &message);
  Parser_state parse_cross_trade_message(Buffer const &buffer, Message &message);
  Parser_state parse_system_directory_message(Buffer const &buffer, Message &message);
  Parser_state parse_system_event_message(Buffer const &buffer, Message &message);
  Parser_state parse_timestamp_message(Buffer const &buffer, Message &message);
  Parser_state parse_order_replace_message(Buffer const &buffer, Message &message);
  Parser_state parse_order_cancel_message(Buffer const &buffer, Message &message);
  Parser_state parse_reg_sho_message(Buffer const &buffer, Message &message);
}

#endif
