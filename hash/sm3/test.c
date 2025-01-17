
// test unit for SM3
// odzhan

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "sm3.h"

uint8_t vectors[64][32]={
{ 0x1a, 0xb2, 0x1d, 0x83, 0x55, 0xcf, 0xa1, 0x7f, 0x8e, 0x61, 0x19, 0x48, 0x31, 0xe8, 0x1a, 0x8f, 
  0x22, 0xbe, 0xc8, 0xc7, 0x28, 0xfe, 0xfb, 0x74, 0x7e, 0xd0, 0x35, 0xeb, 0x50, 0x82, 0xaa, 0x2b  },
{ 0x2d, 0xae, 0xf6, 0x0e, 0x7a, 0x0b, 0x8f, 0x5e, 0x02, 0x4c, 0x81, 0xcd, 0x2a, 0xb3, 0x10, 0x9f, 
  0x2b, 0x4f, 0x15, 0x5c, 0xf8, 0x3a, 0xde, 0xb2, 0xae, 0x55, 0x32, 0xf7, 0x4a, 0x15, 0x7f, 0xdf  },
{ 0xaf, 0x83, 0xa9, 0x66, 0x22, 0x20, 0x57, 0xac, 0x76, 0x12, 0x46, 0xa7, 0x54, 0x3c, 0x58, 0x0d, 
  0x91, 0x11, 0x01, 0x4f, 0x4e, 0x5e, 0x3c, 0xb1, 0x28, 0x1d, 0xb3, 0x31, 0x51, 0x16, 0x03, 0x35  },
{ 0x18, 0x39, 0x20, 0xf0, 0x0e, 0x15, 0xa0, 0x43, 0x3e, 0xe3, 0xa8, 0xfc, 0x90, 0xdd, 0x9a, 0xc1, 
  0x64, 0xc4, 0x14, 0x2c, 0xcf, 0x63, 0xca, 0x18, 0x9a, 0x8f, 0x64, 0x5e, 0xc9, 0x6f, 0xf8, 0xde  },
{ 0xaf, 0xcc, 0x87, 0x0f, 0xa2, 0x0c, 0x50, 0x79, 0x95, 0x49, 0x97, 0x94, 0x37, 0x1e, 0x8c, 0x25, 
  0xe3, 0xa7, 0x31, 0x0f, 0xa7, 0x22, 0x00, 0xc1, 0x09, 0x37, 0x99, 0x73, 0xae, 0x23, 0x68, 0x45  },
{ 0x04, 0x71, 0x33, 0x17, 0xea, 0x89, 0x4e, 0x89, 0x0d, 0x27, 0xfb, 0x1c, 0xf0, 0x80, 0x0e, 0xad, 
  0x81, 0x83, 0xf6, 0x47, 0xfd, 0x2f, 0xd3, 0x11, 0x2d, 0x15, 0x1f, 0x8a, 0xc2, 0x69, 0x61, 0x7c  },
{ 0x40, 0x7b, 0x8b, 0x70, 0x20, 0x99, 0x35, 0x66, 0xd8, 0x15, 0x36, 0x31, 0xa6, 0x7c, 0xe5, 0x83, 
  0x66, 0x47, 0xe6, 0xce, 0xce, 0x0d, 0x61, 0x8c, 0x7b, 0x86, 0x7d, 0x41, 0x6a, 0x52, 0x95, 0xc5  },
{ 0xfa, 0x35, 0x64, 0xff, 0x6f, 0x77, 0x6a, 0x9c, 0xfc, 0x53, 0xa1, 0xf9, 0xb8, 0x6b, 0xd0, 0xdc, 
  0x74, 0x7a, 0x47, 0x31, 0xa4, 0x49, 0x11, 0x6e, 0x45, 0xc0, 0xad, 0x0d, 0x05, 0xf5, 0x64, 0xb7  },
{ 0xb7, 0x86, 0x91, 0x08, 0xf1, 0x51, 0xba, 0x70, 0x67, 0x2e, 0x10, 0x15, 0x3c, 0xc9, 0x0f, 0xc2, 
  0xb5, 0xd4, 0x50, 0x6a, 0x96, 0x3f, 0x03, 0xb6, 0xc5, 0xb4, 0xaa, 0x3b, 0xce, 0xa0, 0x9d, 0x83  },
{ 0xe5, 0xef, 0xbb, 0x13, 0x32, 0x53, 0xd8, 0x86, 0x99, 0x1e, 0xa6, 0x0b, 0x55, 0xc1, 0x3f, 0xb2, 
  0x60, 0x4e, 0xfc, 0x76, 0x3e, 0x72, 0x99, 0xfc, 0x58, 0xb4, 0x41, 0xb0, 0x07, 0xaf, 0xdf, 0xa2  },
{ 0xf0, 0xd0, 0x1a, 0x14, 0xea, 0xf1, 0x40, 0xce, 0xc6, 0xe3, 0xc9, 0x0e, 0x71, 0x46, 0x98, 0xc9, 
  0xce, 0xb0, 0x3c, 0xbb, 0x93, 0x33, 0x0c, 0x70, 0xc2, 0xa3, 0x2f, 0x58, 0x7b, 0x4c, 0x8f, 0x11  },
{ 0x5e, 0x02, 0xae, 0x6a, 0x90, 0x61, 0x13, 0x84, 0x0d, 0x79, 0xea, 0x81, 0x6b, 0xf8, 0xac, 0x73, 
  0x2b, 0xbe, 0xe9, 0x98, 0x01, 0x7a, 0xfd, 0x3e, 0x34, 0xa4, 0xf0, 0xd0, 0x33, 0x6e, 0xf2, 0x0a  },
{ 0xf2, 0x4b, 0xa4, 0xfa, 0x51, 0x5b, 0xc2, 0xce, 0x76, 0x91, 0xf2, 0x47, 0x91, 0x05, 0xe5, 0x7e, 
  0xa2, 0x22, 0xf9, 0x36, 0xd2, 0xdc, 0x07, 0x22, 0xf3, 0xf4, 0x4a, 0x98, 0x45, 0xbb, 0xf6, 0x69  },
{ 0xa3, 0x69, 0x3b, 0x02, 0xb1, 0x87, 0xb4, 0xa0, 0xa0, 0x34, 0x9a, 0x1b, 0x91, 0x13, 0x2f, 0x5e, 
  0x24, 0x68, 0xba, 0xdb, 0xad, 0x0f, 0x37, 0x4e, 0x85, 0x99, 0xe4, 0x0e, 0x49, 0xcf, 0x58, 0x56  },
{ 0x34, 0x4f, 0x85, 0x14, 0x71, 0x10, 0x5f, 0x50, 0x9b, 0x6b, 0x24, 0xc1, 0x8b, 0x92, 0x61, 0xfb, 
  0x7f, 0x8c, 0xe6, 0xb1, 0x70, 0x74, 0x12, 0xf3, 0xe6, 0x35, 0xab, 0x26, 0x4a, 0xfb, 0xef, 0x15  },
{ 0x41, 0xc8, 0xe1, 0xb9, 0x5b, 0xdb, 0xb5, 0xb0, 0x55, 0x1d, 0xfc, 0x44, 0x42, 0x37, 0xd9, 0x06, 
  0x59, 0xc8, 0x93, 0x06, 0x93, 0x8b, 0x87, 0xb5, 0xc9, 0x85, 0xca, 0x75, 0xf5, 0xf4, 0x75, 0x5c  },
{ 0x10, 0x6e, 0x34, 0xa2, 0xb8, 0xc7, 0xbb, 0x13, 0x15, 0x6c, 0xfd, 0xd0, 0xd9, 0x13, 0x79, 0xdc, 
  0xc4, 0x75, 0x43, 0xdc, 0xf9, 0x78, 0x7c, 0x68, 0xae, 0x5e, 0xb5, 0x82, 0x62, 0x0a, 0xe6, 0xe8  },
{ 0xbf, 0xc0, 0xa0, 0x7b, 0xd1, 0xa6, 0xf9, 0x50, 0xba, 0x90, 0x0b, 0x93, 0xce, 0x4d, 0xbd, 0x5b, 
  0x3a, 0x79, 0x05, 0x49, 0x80, 0xc4, 0xe6, 0x5b, 0x80, 0xb0, 0x1b, 0x7c, 0x18, 0xff, 0xbb, 0x7f  },
{ 0x34, 0x28, 0xc2, 0xa2, 0x6d, 0x9d, 0xf6, 0x5d, 0x91, 0xe6, 0xbe, 0x9c, 0xe6, 0x0b, 0x19, 0x33, 
  0x79, 0x03, 0x8b, 0x13, 0x16, 0xc1, 0x1e, 0xfc, 0x83, 0x8c, 0x47, 0xc4, 0xb1, 0xc2, 0x7f, 0x01  },
{ 0x12, 0x3b, 0x5b, 0x7e, 0xb8, 0x60, 0x04, 0x27, 0x6c, 0x4e, 0xa6, 0x4f, 0x15, 0xa8, 0x0b, 0x23, 
  0x4f, 0xdb, 0xa4, 0xcc, 0x4b, 0x25, 0x6a, 0x8c, 0xbc, 0xba, 0x21, 0x4b, 0xd5, 0x2e, 0x7f, 0x52  },
{ 0x18, 0x85, 0x08, 0x04, 0xc9, 0x2e, 0x97, 0xe1, 0x0d, 0xae, 0xac, 0xd8, 0xdd, 0xa0, 0x02, 0x0b, 
  0xbd, 0x69, 0x6a, 0xf1, 0xf1, 0x9e, 0x1e, 0xe6, 0xdc, 0x19, 0xfa, 0x2c, 0xfc, 0x9b, 0x34, 0xd6  },
{ 0x7a, 0x5e, 0xc2, 0x30, 0x95, 0x16, 0x83, 0x2b, 0x8b, 0x42, 0x87, 0x86, 0x15, 0x11, 0xb8, 0x39, 
  0x29, 0x20, 0xe2, 0x47, 0x00, 0xcc, 0x5f, 0x17, 0xe2, 0x2b, 0x4f, 0x51, 0x3d, 0x72, 0xdb, 0x15  },
{ 0x00, 0x54, 0x01, 0xf5, 0x8f, 0x96, 0xd3, 0xdd, 0x7a, 0xde, 0x6a, 0xf5, 0x56, 0x5f, 0xa0, 0x4b, 
  0xc8, 0x8b, 0xc4, 0x65, 0xe7, 0x5c, 0x83, 0xb7, 0x74, 0xd4, 0xad, 0x3a, 0x1c, 0xb5, 0xdf, 0xf3  },
{ 0x37, 0x4b, 0x03, 0xae, 0x83, 0xdf, 0x35, 0x37, 0x53, 0x12, 0x8d, 0x72, 0x37, 0xcc, 0x68, 0xf9, 
  0xc0, 0x36, 0xf4, 0x2d, 0x91, 0xcf, 0x02, 0xa1, 0x0b, 0x4f, 0x3d, 0x5a, 0x7e, 0xa6, 0x11, 0x94  },
{ 0xfb, 0x0f, 0x7c, 0xaf, 0xbe, 0x9a, 0x6c, 0x0e, 0x2c, 0x6c, 0xb8, 0xcf, 0x75, 0xe3, 0x4f, 0x6d, 
  0x44, 0x4d, 0x85, 0xee, 0x7d, 0x9e, 0x46, 0x07, 0xea, 0x8b, 0xb0, 0x2d, 0x2d, 0xa6, 0xaa, 0x8f  },
{ 0x90, 0x92, 0x84, 0xa6, 0x98, 0x30, 0xfa, 0x75, 0xc2, 0x51, 0x16, 0x3a, 0xd0, 0x98, 0xc6, 0x39, 
  0xf5, 0x16, 0x42, 0x52, 0x43, 0x92, 0x11, 0x1e, 0x76, 0xfb, 0x4f, 0x09, 0xb6, 0xd8, 0x31, 0xcc  },
{ 0x30, 0x0c, 0xf9, 0x66, 0xaf, 0x7e, 0x14, 0x1a, 0xa2, 0x83, 0xa8, 0x97, 0xc9, 0x18, 0xe5, 0xcd, 
  0x7b, 0x88, 0x0b, 0x6c, 0x9f, 0xe5, 0x8f, 0xab, 0x94, 0xde, 0x0b, 0x44, 0x9a, 0x70, 0x9a, 0x83  },
{ 0x8f, 0xd0, 0x5c, 0x6b, 0x9c, 0x2a, 0xab, 0x73, 0xf5, 0xc3, 0xde, 0x11, 0xd0, 0xfb, 0x79, 0x28, 
  0x50, 0xcd, 0x81, 0xa9, 0xd9, 0x3a, 0xdc, 0xdb, 0x7b, 0x8c, 0x86, 0x0a, 0x75, 0x65, 0x0e, 0xac  },
{ 0x33, 0x6d, 0x8b, 0x57, 0x9a, 0x20, 0x80, 0x57, 0x33, 0xfc, 0x48, 0x4a, 0x65, 0xaa, 0x9e, 0xca, 
  0x6d, 0x51, 0x2f, 0xd8, 0x9d, 0x38, 0x1f, 0xfc, 0xaf, 0xd7, 0x21, 0x07, 0x3b, 0xae, 0x34, 0xbd  },
{ 0x88, 0xc1, 0xf6, 0xf2, 0x8f, 0xe2, 0xa3, 0xa9, 0xf9, 0x47, 0x9d, 0x2e, 0xd8, 0xff, 0x2c, 0xeb, 
  0x3b, 0x26, 0x0b, 0x1d, 0x91, 0xa4, 0x7f, 0xc3, 0xaf, 0x00, 0x10, 0x9a, 0xca, 0x4e, 0xdb, 0x52  },
{ 0x46, 0xcc, 0x01, 0xc6, 0xef, 0xc0, 0x31, 0xe0, 0x4c, 0x9b, 0x49, 0x0a, 0x3f, 0xb6, 0x0c, 0x2b, 
  0x7d, 0x27, 0x3a, 0x35, 0xb0, 0x03, 0xfd, 0x1f, 0x3e, 0x22, 0x7b, 0xc5, 0x8e, 0x88, 0x6c, 0x54  },
{ 0x12, 0x19, 0x18, 0x39, 0xe9, 0x91, 0x63, 0xc2, 0x11, 0xa0, 0xfc, 0x05, 0x14, 0x85, 0xe3, 0xa3, 
  0x44, 0x43, 0x75, 0x85, 0x29, 0xd3, 0x8e, 0x93, 0xc6, 0xb7, 0x92, 0x6b, 0x82, 0xf2, 0x6d, 0x89  },
{ 0xe0, 0xba, 0xb8, 0xf4, 0xd8, 0x17, 0x2b, 0xa2, 0x45, 0x19, 0x0d, 0x13, 0xc9, 0x41, 0x17, 0xe9, 
  0x3b, 0x82, 0x16, 0x6c, 0x25, 0xb2, 0xb6, 0x98, 0x83, 0x35, 0x0c, 0x19, 0x2c, 0x90, 0x51, 0x40  },
{ 0x8f, 0xa0, 0xdd, 0x2c, 0x79, 0x8c, 0x5b, 0xba, 0xda, 0x41, 0x5e, 0x5d, 0x11, 0x67, 0xa3, 0x70, 
  0x72, 0xee, 0x65, 0x55, 0x8a, 0x2c, 0xea, 0x40, 0x8b, 0xc5, 0x21, 0x4c, 0x9f, 0xd2, 0x8f, 0x3c  },
{ 0x49, 0xcb, 0x1d, 0xa7, 0x13, 0xc9, 0x6d, 0xbc, 0xc6, 0xae, 0x4e, 0xb3, 0x42, 0x2a, 0x8c, 0x5d, 
  0xc8, 0xf1, 0x89, 0x76, 0x78, 0x2f, 0xcd, 0x6c, 0xbc, 0xfc, 0x03, 0x0c, 0x83, 0x54, 0x9e, 0x57  },
{ 0x78, 0x54, 0x9d, 0xab, 0xeb, 0xaa, 0x14, 0xde, 0xe4, 0x9e, 0x98, 0xf0, 0xeb, 0x01, 0xdc, 0xb6, 
  0xda, 0x5f, 0xb0, 0x61, 0xdd, 0x6d, 0xb1, 0xf2, 0x1f, 0x8f, 0xe4, 0xfb, 0xd7, 0x5b, 0x10, 0x29  },
{ 0xee, 0x9d, 0x28, 0xda, 0xd8, 0x81, 0xd7, 0xf5, 0x91, 0x89, 0x9b, 0x4d, 0x10, 0x5e, 0x38, 0x5b, 
  0x19, 0x90, 0x11, 0x1f, 0x62, 0x46, 0x34, 0xd3, 0xe1, 0xd5, 0x81, 0x17, 0x7c, 0x2f, 0x04, 0xb0  },
{ 0xc3, 0x8a, 0xd8, 0x54, 0x46, 0x46, 0x7c, 0x23, 0x67, 0x07, 0xb2, 0x37, 0xf3, 0xc4, 0x93, 0x34, 
  0x17, 0x68, 0x84, 0xe5, 0x91, 0x34, 0xce, 0x52, 0x30, 0xd5, 0xbe, 0xb8, 0x4c, 0xf6, 0x59, 0x29  },
{ 0xc2, 0x85, 0x37, 0xce, 0x34, 0xb0, 0xa1, 0xc9, 0x39, 0xf1, 0xfe, 0xba, 0xcb, 0x14, 0x96, 0xc7, 
  0xfe, 0xeb, 0xa7, 0x58, 0xfc, 0x86, 0x77, 0x31, 0x3b, 0x98, 0x66, 0xbd, 0xab, 0x42, 0xd2, 0x28  },
{ 0x70, 0x75, 0x94, 0x1a, 0xe1, 0x78, 0x0f, 0x31, 0xb0, 0xf8, 0xf2, 0x30, 0x82, 0x46, 0x81, 0xa8, 
  0xc7, 0x1a, 0x91, 0x67, 0xb1, 0x29, 0x67, 0xc0, 0xd3, 0xbf, 0x64, 0xff, 0x1e, 0xa6, 0x37, 0xed  },
{ 0x79, 0xf6, 0x22, 0x22, 0xb7, 0xf9, 0xd0, 0xeb, 0x5c, 0xbd, 0x44, 0x59, 0xfc, 0xd4, 0x7f, 0x6d, 
  0x24, 0x40, 0x03, 0xd4, 0x16, 0x42, 0x7b, 0x06, 0x96, 0x56, 0x07, 0x72, 0xb0, 0x5a, 0x73, 0x59  },
{ 0x2a, 0xea, 0x4b, 0x1d, 0x0c, 0x2b, 0x92, 0x15, 0xbf, 0x36, 0xed, 0x1c, 0x6f, 0xc8, 0x40, 0x5c, 
  0x86, 0x4a, 0x51, 0x5e, 0x40, 0x55, 0x93, 0x56, 0xa9, 0x84, 0x2a, 0xb6, 0x8c, 0xcd, 0x7e, 0x13  },
{ 0xaf, 0x4d, 0xcd, 0xfe, 0x7a, 0x01, 0x09, 0x42, 0xe3, 0xc5, 0xc6, 0x2d, 0xc1, 0xef, 0x7e, 0x90, 
  0x5a, 0x2e, 0x71, 0x92, 0x21, 0xf8, 0xb8, 0x3d, 0xe6, 0x57, 0x40, 0x5a, 0xd2, 0x91, 0x65, 0xdf  },
{ 0x2e, 0x57, 0x50, 0xf4, 0xf3, 0xd2, 0x9d, 0x6f, 0xa7, 0x05, 0xbc, 0x0b, 0x0b, 0x89, 0xea, 0xa6, 
  0xd6, 0x8c, 0x20, 0x21, 0x8c, 0x8e, 0x7f, 0x19, 0x03, 0xca, 0xa3, 0x4c, 0xdf, 0xd4, 0x77, 0x7d  },
{ 0xc5, 0xc4, 0xc0, 0xe2, 0x0c, 0xf3, 0x3c, 0xca, 0xbf, 0x74, 0x12, 0x6a, 0x05, 0x04, 0xc0, 0x62, 
  0xed, 0xec, 0x23, 0x08, 0xef, 0xfd, 0xda, 0x5d, 0xb8, 0xec, 0x45, 0x9a, 0x4a, 0x88, 0xcf, 0xe7  },
{ 0x3c, 0x8a, 0xf5, 0x98, 0x0a, 0x30, 0xce, 0xde, 0x0a, 0x4a, 0x78, 0x62, 0x57, 0xa4, 0xb2, 0x49, 
  0x5c, 0x36, 0x05, 0xed, 0xca, 0xc5, 0x85, 0x65, 0x83, 0x90, 0x71, 0xe2, 0xc7, 0x18, 0xd3, 0xdf  },
{ 0x41, 0x56, 0xd9, 0xdc, 0xe7, 0xc7, 0xeb, 0x9b, 0xc1, 0xdf, 0x68, 0x0b, 0x84, 0x72, 0xfd, 0xfc, 
  0x35, 0xd9, 0xde, 0xb9, 0x33, 0xa2, 0xb7, 0x10, 0xe8, 0x72, 0x10, 0xdf, 0x62, 0xdd, 0x9d, 0xba  },
{ 0x3c, 0x27, 0x7a, 0xb9, 0x06, 0x80, 0x2e, 0x93, 0x66, 0xe0, 0x50, 0x9d, 0x0f, 0x70, 0xed, 0xa2, 
  0xf1, 0xd1, 0xaa, 0x37, 0x90, 0xc0, 0x10, 0x03, 0xdb, 0xf5, 0xc1, 0x7e, 0x3e, 0x8c, 0x8c, 0x8e  },
{ 0xc4, 0xce, 0x52, 0x70, 0xca, 0x07, 0x17, 0x01, 0xed, 0xc9, 0x01, 0x0d, 0x24, 0xdc, 0x09, 0x9d, 
  0xaf, 0xc1, 0x71, 0x45, 0xb6, 0xb7, 0x0d, 0xc8, 0x3c, 0x46, 0x18, 0xaf, 0xe0, 0xe2, 0xa0, 0x89  },
{ 0x28, 0x7e, 0xf4, 0x4c, 0x88, 0xc4, 0xce, 0x55, 0xd1, 0x3f, 0x3a, 0xc6, 0x2a, 0xe4, 0xcd, 0x6a, 
  0x6b, 0xb3, 0xe3, 0x97, 0x57, 0x3f, 0x83, 0x1e, 0xaa, 0x10, 0x58, 0xd9, 0x03, 0x75, 0xbf, 0x41  },
{ 0xeb, 0x63, 0xcd, 0xae, 0xea, 0xce, 0x36, 0xd7, 0x19, 0xac, 0xf4, 0x05, 0x08, 0x25, 0x87, 0x90, 
  0x04, 0x00, 0x3c, 0xfa, 0x1b, 0xf2, 0x5c, 0x65, 0x2e, 0xc6, 0x43, 0xce, 0xce, 0x1e, 0x2e, 0x08  },
{ 0x3d, 0x62, 0xaa, 0x1a, 0xef, 0xd4, 0x31, 0x3c, 0x81, 0xbc, 0xef, 0x6b, 0x20, 0x80, 0x07, 0x63, 
  0xdf, 0x5f, 0xb1, 0x1d, 0xac, 0x95, 0xbf, 0x72, 0x33, 0xa0, 0xd6, 0x7f, 0x73, 0xad, 0x56, 0xd0  },
{ 0xcb, 0x66, 0x46, 0xad, 0x84, 0x9f, 0x88, 0x90, 0xbe, 0x64, 0xcb, 0xde, 0x4f, 0xad, 0x68, 0xa2, 
  0x27, 0x08, 0x82, 0x1e, 0x60, 0x70, 0x43, 0x2f, 0x5f, 0x42, 0xdd, 0x73, 0x34, 0x46, 0xc0, 0x81  },
{ 0xa2, 0xbd, 0x7a, 0x24, 0xc6, 0x9d, 0x2b, 0x25, 0x76, 0xd8, 0xfb, 0x42, 0x71, 0xfc, 0x51, 0x70, 
  0x5d, 0xbb, 0x16, 0x5d, 0x79, 0xfb, 0x57, 0xff, 0x24, 0x27, 0x75, 0x15, 0xcd, 0x7f, 0x49, 0xd1  },
{ 0xee, 0x84, 0x99, 0xc4, 0x4e, 0xb5, 0xb7, 0x08, 0xc3, 0xb7, 0x99, 0xc1, 0xbd, 0xb3, 0xb2, 0x1f, 
  0xd6, 0xdb, 0x97, 0x2c, 0x08, 0x1c, 0x52, 0xcc, 0x1c, 0x6e, 0x3d, 0xd6, 0x4d, 0xb4, 0x84, 0xe4  },
{ 0x2c, 0xdc, 0xe3, 0xd6, 0x97, 0xaf, 0x37, 0x16, 0xa9, 0xb3, 0xcd, 0xf0, 0x68, 0xb4, 0x3e, 0x51, 
  0x38, 0x46, 0xe1, 0x7c, 0xc9, 0xfd, 0x42, 0x79, 0x29, 0xaa, 0xd7, 0x01, 0x65, 0xf2, 0x1d, 0xda  },
{ 0x87, 0xb8, 0x1a, 0xf2, 0xb2, 0xb2, 0x2c, 0xbd, 0xf2, 0x68, 0xe2, 0x11, 0xd0, 0x12, 0xd6, 0x04, 
  0x89, 0x2d, 0x3c, 0x94, 0x8f, 0xf2, 0x98, 0xd6, 0x1d, 0x6c, 0x94, 0x2e, 0xee, 0x84, 0x7f, 0x86  },
{ 0xed, 0x7e, 0x64, 0xaf, 0xf8, 0x7f, 0xb6, 0x36, 0x98, 0x43, 0xe9, 0x30, 0x5b, 0xe1, 0x3d, 0x0d, 
  0xaf, 0x34, 0x59, 0xda, 0x4e, 0x1d, 0x25, 0x75, 0xaa, 0x8e, 0x08, 0x80, 0x4e, 0xc0, 0x2d, 0x22  },
{ 0xd2, 0x80, 0x95, 0xd6, 0xc6, 0x20, 0x35, 0xa5, 0x84, 0xc2, 0x9b, 0x0e, 0x36, 0x17, 0xe0, 0xea, 
  0xe3, 0x45, 0x4b, 0x86, 0xfa, 0xe6, 0xcf, 0xfb, 0xf8, 0x88, 0x43, 0x1a, 0x4c, 0x9d, 0xd7, 0x6a  },
{ 0xc9, 0x47, 0x9e, 0x0e, 0xad, 0xe8, 0xd7, 0x88, 0x7f, 0x0d, 0x03, 0x03, 0x44, 0x6c, 0x07, 0x9b, 
  0xbe, 0x4e, 0x54, 0xc1, 0x5d, 0x5b, 0xfb, 0xde, 0x84, 0x38, 0x8a, 0x33, 0xe0, 0xc3, 0x54, 0x8e  },
{ 0xc9, 0x42, 0xff, 0xfc, 0x60, 0x82, 0x68, 0xbb, 0xd8, 0xf7, 0xaf, 0xb2, 0x3d, 0x9a, 0x4f, 0xde, 
  0x41, 0x7d, 0xb6, 0xaa, 0x69, 0xd4, 0x75, 0x25, 0x0a, 0xf8, 0x9c, 0x87, 0xeb, 0x95, 0x58, 0x60  },
{ 0x98, 0x58, 0xf7, 0x10, 0x59, 0xb2, 0xbc, 0xc1, 0x17, 0xdf, 0x33, 0x3d, 0x2b, 0x37, 0xac, 0x19, 
  0x4b, 0xee, 0x70, 0x73, 0x7d, 0x07, 0x58, 0x97, 0x30, 0x50, 0x32, 0xb3, 0x12, 0x85, 0x93, 0x13  },
{ 0x0e, 0x03, 0xd5, 0xe8, 0xe9, 0x8b, 0x69, 0x15, 0x01, 0xb2, 0x5b, 0xd6, 0x2a, 0xdc, 0x7c, 0x47, 
  0x83, 0xd8, 0x14, 0xd1, 0x29, 0x70, 0xc3, 0xe3, 0xff, 0x8a, 0x8b, 0xeb, 0x11, 0x19, 0x59, 0xc2  },
{ 0x52, 0x41, 0xdc, 0x10, 0xcb, 0x3c, 0x70, 0x0e, 0x46, 0x44, 0x69, 0x43, 0xd2, 0x7b, 0x97, 0x1f, 
  0xef, 0xa7, 0xe8, 0x81, 0x15, 0xf8, 0x66, 0xd6, 0xf8, 0x3d, 0x50, 0x2f, 0xf1, 0xbc, 0x06, 0xc2  }};
 
int main(int argc, char *argv[])
{
  SM3_CTX ctx;
  int     i, fail;
  uint8_t out[32]={0};  
  uint8_t msg[64];

  for (fail=0, i=0; i<64; i++) {
    memset(msg, 0, sizeof(msg));
    msg[i] = i;
    
    SM3_Init(&ctx);
    SM3_Update(&ctx, msg, i);
    SM3_Final(out, &ctx);
  
    if (memcmp(out, vectors[i], 32)) {
      printf ("Hash for test vector %i failed\n", i+1);
      fail++;
    }      
  }
  if (!fail) printf ("All SM3 tests passed\n");  

  return 0;
}