#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdint>

#include <itch_parser.hh>
#include <endian_conversion.hh>

#include "message_dispatcher.hh"


using namespace std;
using namespace Itch4;


int main() {
  std::ios_base::sync_with_stdio(false);

  
  istream &file = cin;

  if (file) {
    int16_t packet_length;

    Buffer b;
    b.reserve(Itch4::LARGEST_MESSAGE); 

    Message msg;
    Parser_state p_state;

    unsigned long long counter = 0; 

    Message_switch_count message_dispatcher;
    
    while(file.read(reinterpret_cast<char*>(&packet_length), 2)) {
      // Parse soupBinTCP
      // Get the packet length
      packet_length = Itch4::network_to_host_16(packet_length); 
      
      // Get the payload (message)
      if(file.read(reinterpret_cast<char*>(&b.front()), packet_length)) {
            
        // Parse the message
        p_state = parse_buffer(b, msg);
        
        switch(p_state) {
        case PS_SUCCESS:
          msg.dispatch(message_dispatcher);
          break;
        case PS_NEED_MORE: cout << "need more" << endl; break;
        case PS_PARSE_ERROR: cout << "parse error" << endl; exit(1); break;
        default: break;
        }
        counter++;
      }
    }
    cout << counter << endl;
    message_dispatcher.print_counts();
  }
  else {
    cout << "Unable to open file";
  }

  return 0;

}
