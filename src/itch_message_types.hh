#ifndef ITCH_MESSAGE_TYPES_HH
#define ITCH_MESSAGE_TYPES_HH

#include <itch_types.hh>
#include <max_integer.hh>

#define MAX(T1, EXPR) (Max<sizeof (T1), EXPR>::val)

namespace Itch4 {
  struct Timestamp_message {
    Seconds seconds;
  };

  struct System_event_message {
    Nanoseconds nanoseconds;
    System_event_code sec;
  };

  struct Stock_directory_message {
    Nanoseconds nanoseconds;
    Stock_symbol stock_symbol;
    Market_category market_category;
    Financial_status_indicator financial_status_indicator;
    Round_lot_size round_lot_size;
    Round_lots_only round_lots_only;
  };

  struct Stock_trading_action_message {
    Nanoseconds nanoseconds;
    Stock_symbol stock_symbol;
    Trading_state trading_state;
    Fixed_array<unsigned char, 4> reason;
  };

  struct Reg_sho_message {
    Nanoseconds nanoseconds;
    Stock_symbol stock_symbol;
    Reg_sho_action reg_sho_action;
  };

  struct Market_participant_message {
    Nanoseconds nanoseconds;
    Mpid mpid;
    Stock_symbol stock_symbol;
    Primary_market_maker primary_market_maker;
    Market_maker_mode market_maker_mode;
    Market_participant_state market_participant_state;
  };

  struct Add_order_no_mpid_message {
    Nanoseconds nanoseconds;
    Order_reference_number order_reference_number;
    Buy_sell_indicator buy_sell_indicator;
    Shares shares;
    Stock_symbol stock_symbol;
    Price price;
  };

  struct Add_order_with_mpid_message {
    Nanoseconds nanoseconds;
    Order_reference_number order_reference_number;
    Buy_sell_indicator buy_sell_indicator;
    Shares shares;
    Stock_symbol stock_symbol;
    Price price;
    Attribution attribution;
  };

  struct Order_executed_message {
    Nanoseconds nanoseconds;
    Order_reference_number order_reference_number;
    Shares executed_shares;
    Match_number match_number;
  };

  struct Order_executed_with_price_message {
    Nanoseconds nanoseconds;
    Order_reference_number order_reference_number;
    Shares executed_shares;
    Match_number match_number;
    Printable printable;
    Price execution_price;
  };

  struct Order_cancel_message {
    Nanoseconds nanoseconds;
    Order_reference_number order_reference_number;
    Shares canceled_shares;
  };

  struct Order_delete_message {
    Nanoseconds nanoseconds;
    Order_reference_number order_reference_number;
  };

  struct Order_replace_message {
    Nanoseconds nanoseconds;
    Order_reference_number original_order_reference_number;
    Order_reference_number new_order_reference_number;
    Shares shares;
    Price price;
  };

  struct Trade_message {
    Nanoseconds nanoseconds;
    Order_reference_number order_reference_number;
    Buy_sell_indicator buy_sell_indicator;
    Shares shares;
    Stock_symbol stock_symbol;
    Price price;
    Match_number match_number;
  };

  struct Cross_trade_message {
    Nanoseconds nanoseconds;
    Shares shares;
    Stock_symbol stock_symbol;
    Price cross_price;
    Match_number match_number;
    Cross_type cross_type;
  };

  struct Broken_trade_message {
    Nanoseconds nanoseconds;
    Match_number match_number;
  };

  struct Net_order_imbalance_indicator_message {
    Nanoseconds nanoseconds;
    Shares paired_shares;
    Shares imbalance_shares;
    Imbalance_direction imbalance_direction;
    Stock_symbol stock_symbol;
    Price far_price;
    Price near_price;
    Price current_reference_price;
    Cross_type cross_type;
    Price_variation_indicator price_variation_indicator;
  };

  /*
   * Absolutely ridiculous
   */
  const size_t LARGEST_MESSAGE = MAX(Timestamp_message,
                                     MAX(System_event_message,
                                         MAX(Stock_directory_message,
                                             MAX(Stock_trading_action_message,
                                                 MAX(Reg_sho_message,
                                                     MAX(Market_participant_message,
                                                         MAX(Add_order_no_mpid_message,
                                                             MAX(Add_order_with_mpid_message,
                                                                 MAX(Order_executed_message,
                                                                     MAX(Order_executed_with_price_message,
                                                                         MAX(Order_cancel_message,
                                                                             MAX(Order_replace_message,
                                                                                 (Max<sizeof (Broken_trade_message),
                                                                                  sizeof (Net_order_imbalance_indicator_message)>::val)))))))))))));

                                                                                         
  
}


#endif
