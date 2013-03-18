#ifndef ENDIAN_CONVERSION_HH
#define ENDIAN_CONVERSION_HH

#include <cstdint>

namespace Itch4 {
  
#ifdef LITTLE_ENDIAN
  inline std::uint16_t network_to_host_16(std::uint16_t i) {
    return ((i >> 8) |
            (i << 8));
  }

  inline std::uint32_t network_to_host_32(std::uint32_t i) {
    return (((i & 0xff000000) >> 24) |
            ((i & 0x00ff0000) >>  8) |
            ((i & 0x0000ff00) <<  8) |
            ((i & 0x000000ff) << 24));    
  }

  inline std::uint64_t network_to_host_64(std::uint64_t i) {
    return (((i & 0xff00000000000000ull) >> 56) |
            ((i & 0x00ff000000000000ull) >> 40) |
            ((i & 0x0000ff0000000000ull) >> 24) |
            ((i & 0x000000ff00000000ull) >> 8 ) |
            ((i & 0x00000000ff000000ull) << 8 ) |
            ((i & 0x0000000000ff0000ull) << 24) |
            ((i & 0x000000000000ff00ull) << 40) |
            ((i & 0x00000000000000ffull) << 56));
  }

  inline std::uint16_t host_to_network_16(std::uint16_t i) {
    return network_to_host_16(i);
  }

  inline std::uint32_t host_to_network_32(std::uint32_t i) {
    return network_to_host_32(i);
  }

  inline std::uint64_t host_to_network_64(std::uint64_t i) {
    return network_to_host_64(i);
  }

#else
  /*
   * If we aren't little endian than define these as nothing
   * the optimizer should remove them for us
   */
  inline std::uint16_t network_to_host_16(std::uint16_t i) {
    return i;
  }

  inline std::uint32_t network_to_host_32(std::uint32_t i) {
    return i;
  }

  inline std::uint64_t network_to_host_64(std::uint64_t i) {
    return i;
  }

  inline std::uint16_t host_to_network_16(std::uint16_t i) {
    return i;
  }

  inline std::uint32_t host_to_network_32(std::uint32_t i) {
    return i;
  }

  inline std::uint64_t host_to_network_64(std::uint64_t i) {
    return i;
  }
#endif
  
}
#endif
