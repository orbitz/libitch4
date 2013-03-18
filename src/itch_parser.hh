#ifndef ITCH_PARSER_HH
#define ITCH_PARSER_HH

#include <itch_buffer.hh>

namespace Itch4 {
  enum Parser_state {
    PS_SUCCESS,
    PS_NEED_MORE,
    PS_PARSE_ERROR
  };

  enum Dispatch_error {
    D_SUCCESS,
    D_UNKNOWN_MESSAGE,
    D_ERROR
  };
  
  struct Message_switch {
    virtual Dispatch_error handle(Timestamp_message const &timestamp_message) = 0;
    virtual Dispatch_error handle(System_event_message const &system_event_message) = 0;
    virtual Dispatch_error handle(Stock_directory_message const &stock_directory_message) = 0;
    virtual Dispatch_error handle(Stock_trading_action_message const &stock_trading_action_message) = 0;
    virtual Dispatch_error handle(Reg_sho_message const &reg_sho_message) = 0;
    virtual Dispatch_error handle(Market_participant_message const &market_participant_message) = 0;
    virtual Dispatch_error handle(Add_order_no_mpid_message const &add_order_no_mpid_message) = 0;
    virtual Dispatch_error handle(Add_order_with_mpid_message const &add_order_with_mpid_message) = 0;
    virtual Dispatch_error handle(Order_executed_message const &order_executed_message) = 0;
    virtual Dispatch_error handle(Order_executed_with_price_message const &order_executed_with_price_message) = 0;
    virtual Dispatch_error handle(Order_cancel_message const &order_cancel_message) = 0;
    virtual Dispatch_error handle(Order_delete_message const &order_delete_message) = 0;
    virtual Dispatch_error handle(Order_replace_message const &order_replace_message) = 0;
    virtual Dispatch_error handle(Trade_message const &trade_message) = 0;
    virtual Dispatch_error handle(Cross_trade_message const &cross_trade_message) = 0;
    virtual Dispatch_error handle(Broken_trade_message const &broken_trade_message) = 0;
    virtual Dispatch_error handle(Net_order_imbalance_indicator_message const &net_order_imbalance_indicator_message) = 0;
  };

  struct Message_switch_noop : public Message_switch {
    Dispatch_error handle(Timestamp_message const &) { return D_SUCCESS; }
    Dispatch_error handle(System_event_message const &) { return D_SUCCESS; }
    Dispatch_error handle(Stock_directory_message const &) { return D_SUCCESS; }
    Dispatch_error handle(Stock_trading_action_message const &) { return D_SUCCESS; }
    Dispatch_error handle(Reg_sho_message const &) { return D_SUCCESS; }
    Dispatch_error handle(Market_participant_message const &) { return D_SUCCESS; }
    Dispatch_error handle(Add_order_no_mpid_message const &) { return D_SUCCESS; }
    Dispatch_error handle(Add_order_with_mpid_message const &) { return D_SUCCESS; }
    Dispatch_error handle(Order_executed_message const &) { return D_SUCCESS; }
    Dispatch_error handle(Order_executed_with_price_message const &) { return D_SUCCESS; }
    Dispatch_error handle(Order_cancel_message const &) { return D_SUCCESS; }
    Dispatch_error handle(Order_delete_message const &) { return D_SUCCESS; }
    Dispatch_error handle(Order_replace_message const &) { return D_SUCCESS; }
    Dispatch_error handle(Trade_message const &) { return D_SUCCESS; }
    Dispatch_error handle(Cross_trade_message const &) { return D_SUCCESS; }
    Dispatch_error handle(Broken_trade_message const &) { return D_SUCCESS; }
    Dispatch_error handle(Net_order_imbalance_indicator_message const &) { return D_SUCCESS; }
  };
  
  struct Message {
    Dispatch_error dispatch(Message_switch &message_switch) const;

    Message_types message_type() const {
      return current_message;
    }
    
    Message_types current_message;
    
    union {
      Timestamp_message timestamp_message;
      System_event_message system_event_message;
      Stock_directory_message stock_directory_message;
      Stock_trading_action_message stock_trading_action_message;
      Reg_sho_message reg_sho_message;
      Market_participant_message market_participant_message;
      Add_order_no_mpid_message add_order_no_mpid_message;
      Add_order_with_mpid_message add_order_with_mpid_message;
      Order_executed_message order_executed_message;
      Order_executed_with_price_message order_executed_with_price_message;
      Order_cancel_message order_cancel_message;
      Order_delete_message order_delete_message;
      Order_replace_message order_replace_message;
      Trade_message trade_message;
      Cross_trade_message cross_trade_message;
      Broken_trade_message broken_trade_message;
      Net_order_imbalance_indicator_message net_order_imbalance_indicator_message;
    } message_types;
  };
  
  
  Parser_state parse_buffer(Buffer &buffer, Message &message);
}

#endif
