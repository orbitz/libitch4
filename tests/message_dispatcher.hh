#ifndef MESSAGE_DISPATCHER_HH
#define MESSAGE_DISPATCHER_HH

#include <iostream>
#include <array>

#include <itch_types.hh>
#include <itch_parser.hh>

namespace {
  using namespace Itch4;
  
  struct Message_switch_count : public Message_switch {
    std::array<unsigned long long, 256> counts;

    Message_switch_count() : counts()
    {}

    
    Dispatch_error handle(Timestamp_message const &) {
      counts[MT_TIMESTAMP] += 1;
      return D_SUCCESS;
    }
    
    Dispatch_error handle(System_event_message const &) {
      counts[MT_SEM] += 1;
      return D_SUCCESS;
    }
    
    Dispatch_error handle(Stock_directory_message const &) {
      counts[MT_SDM] += 1;
      return D_SUCCESS;
    }
    
    Dispatch_error handle(Stock_trading_action_message const &) {
      counts[MT_STAM] += 1;
      return D_SUCCESS;
    }
    
    Dispatch_error handle(Reg_sho_message const &) {
      counts[MT_RSSSPTM] += 1;
      return D_SUCCESS;
    }
    
    Dispatch_error handle(Market_participant_message const &) {
      counts[MT_MPPM] += 1;
      return D_SUCCESS;
    }
    
    Dispatch_error handle(Add_order_no_mpid_message const &) {
      counts[MT_AONMM] += 1;
      return D_SUCCESS;
    }
    
    Dispatch_error handle(Add_order_with_mpid_message const &) {
      counts[MT_AOWMM] += 1;
      return D_SUCCESS;
    }
    
    Dispatch_error handle(Order_executed_message const &) {
      counts[MT_OEM] += 1;
      return D_SUCCESS;
    }
    
    Dispatch_error handle(Order_executed_with_price_message const &) {
      counts[MT_OEWPM] += 1;
      return D_SUCCESS;
    }
    
    Dispatch_error handle(Order_cancel_message const &) {
      counts[MT_OCM] += 1;
      return D_SUCCESS;
    }
    
    Dispatch_error handle(Order_delete_message const &) {
      counts[MT_ODM] += 1;
      return D_SUCCESS;
    }
    
    Dispatch_error handle(Order_replace_message const &) {
      counts[MT_ORM] += 1;
      return D_SUCCESS;
    }
    
    Dispatch_error handle(Trade_message const &) {
      counts[MT_TRADEM] += 1;
      return D_SUCCESS;
    }
    
    Dispatch_error handle(Cross_trade_message const &) {
      counts[MT_CROSSTRADEM] += 1;
      return D_SUCCESS;
    }
    
    Dispatch_error handle(Broken_trade_message const &) {
      counts[MT_BROKENTRADEM] += 1;
      return D_SUCCESS;
    }
    
    Dispatch_error handle(Net_order_imbalance_indicator_message const &) {
      counts[MT_NOIIM] += 1;
      return D_SUCCESS;
    }

    void print_counts() const {
      std::cout << "MT_TIMESTAMP " << counts[MT_TIMESTAMP] << '\n';
      std::cout << "MT_SEM " << counts[MT_SEM] << '\n';
      std::cout << "MT_SDM " << counts[MT_SDM] << '\n';
      std::cout << "MT_STAM " << counts[MT_STAM] << '\n';
      std::cout << "MT_RSSSPTM " << counts[MT_RSSSPTM] << '\n';
      std::cout << "MT_MPPM " << counts[MT_MPPM] << '\n';
      std::cout << "MT_AONMM " << counts[MT_AONMM] << '\n';
      std::cout << "MT_AOWMM " << counts[MT_AOWMM] << '\n';
      std::cout << "MT_OEM " << counts[MT_OEM] << '\n';
      std::cout << "MT_OEWPM " << counts[MT_OEWPM] << '\n';
      std::cout << "MT_OCM " << counts[MT_OCM] << '\n';
      std::cout << "MT_ODM " << counts[MT_ODM] << '\n';
      std::cout << "MT_ORM " << counts[MT_ORM] << '\n';
      std::cout << "MT_TRADEM " << counts[MT_TRADEM] << '\n';
      std::cout << "MT_CROSSTRADEM " << counts[MT_CROSSTRADEM] << '\n';
      std::cout << "MT_BROKENTRADEM " << counts[MT_BROKENTRADEM] << '\n';
      std::cout << "MT_NOIIM " << counts[MT_NOIIM] << '\n';
    }
    
  };

}

#endif
