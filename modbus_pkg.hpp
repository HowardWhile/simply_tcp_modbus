#ifndef ARC_MODBUS_MODBUS_PKG_H_
#define ARC_MODBUS_MODBUS_PKG_H_

#include <vector>
#include <math.h>

// https://www.simplymodbus.ca/TCP.htm
#define MB_TCP_Transaction_Identifier_Index 0
#define MB_TCP_Transaction_Identifier_LEN 2
#define MB_TCP_Protocol_Identifier_Index 2
#define MB_TCP_Protocol_Identifier_LEN 2
#define MB_TCP_Message_Length_Index 4
#define MB_TCP_Message_Length_LEN 2
#define MB_TCP_Unit_Identifier_Index MB_TCP_Message_Length_Index + MB_TCP_Message_Length_LEN
#define MB_TCP_Unit_Identifier_LEN 1
#define MB_TCP_MBAP_HEADER_LEN MB_TCP_Transaction_Identifier_LEN + MB_TCP_Protocol_Identifier_LEN + MB_TCP_Message_Length_LEN + MB_TCP_Unit_Identifier_LEN // 7

#define MB_TCP_FC_IDX

namespace arc_modbus
{
    typedef enum type_ReadRequestPkg
    {
        READ_RW_BITS = 1,
        READ_RO_BITS,
        READ_RW_REGS,
        READ_RO_REGS
    };


    class modbus_tcp_pkg
    {
    private:
        typedef union tu_16
        {
            short int16_view;
            char int8_view[2];
        };

        int slave_id;

        int k_PLC_ADDRESS_BASE;    

        int get_response_len(int fc, int data_len)
        {
            switch (fc)
            {
            case 1:
            case 2:
                return 6 + Math.floor((length - 1) / 8);
                break;
            
            default:
                break;
            }
        }

    public:

        modbus_tcp_pkg(int iAddrBase, int iSlaveID) 
        {
            this->k_PLC_ADDRESS_BASE = iAddrBase; // 0 or 1
            this->slave_id = iSlaveID;
        }
        ~modbus_tcp_pkg() {}        


        std::vector<char> ReadRequest(type_ReadRequestPkg iType, int iAddress, int iNum, int &oResponseLength)
        {

        }

        std::vector<char> WriteRequest(int iAddress, bool iBit, int &oResponseLength)
        {

        }

        std::vector<char> WriteRequest(int iAddress, std::vector<bool> iBits, int &oResponseLength)
        {

        }

        std::vector<char> WriteRequest(int iAddress, short iReg, int &oResponseLength)
        {

        }

        std::vector<char> WriteRequest(int iAddress, std::vector<short> iRegs, int &oResponseLength)
        {

        }




        int WriteRequest
    };
} // namespace arc_modbus

#endif