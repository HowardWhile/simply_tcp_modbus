#ifndef ARC_MODBUS_MODBUS_PKG_H_
#define ARC_MODBUS_MODBUS_PKG_H_

#include <vector>
#include <stdint.h>
#include <math.h>

// https://www.simplymodbus.ca/TCP.htm
#define MB_TCP_Transaction_Identifier_IDX 0
#define MB_TCP_Protocol_Identifier_IDX 2
#define MB_TCP_Message_Length_IDX 4

#define MB_SlaveID_IDX 0
#define MB_FuncCode_IDX 1
#define MB_RegsAddress_IDX 2
#define MB_RegsNumber_IDX 4

#define MB_TCP_HEADER_OFFSET 6



#define MB_TCP_MBAP_HEADER_LEN MB_TCP_Transaction_Identifier_LEN + MB_TCP_Protocol_Identifier_LEN + MB_TCP_Message_Length_LEN + MB_TCP_Unit_Identifier_LEN // 7

#define MB_TCP_FC_IDX

namespace arc_modbus
{
    enum type_ReadRequestPkg
    {
        READ_RW_BITS = 1,
        READ_RO_BITS,
        READ_RW_REGS,
        READ_RO_REGS
    };

    union tu_16
    {
        short int16_view;
        char int8_view[2];
    };

    class modbus_tcp_pkg
    {  

    public:

        modbus_tcp_pkg(int iAddrBase, int iSlaveID) 
        {
            this->k_PLC_ADDRESS_BASE = iAddrBase; // 0 or 1
            this->slave_id = iSlaveID;
        }
        ~modbus_tcp_pkg() {}

        

        std::vector<char> ReadRequest(type_ReadRequestPkg iType, uint16_t iAddress, int iNumber, int &oResponseLength)
        {
            // FC 01 02 03 04

            tu_16 cTool; // convert tool
            std::vector<char> pkg; // return value 

            // Function code 
            pkg.push_back((char)iType);
            // Address            
            cTool.int16_view = iAddress;
            pkg.push_back(cTool.int8_view[1]);
            pkg.push_back(cTool.int8_view[0]);
            // Number
            cTool.int16_view = iNumber;
            pkg.push_back(cTool.int8_view[1]);
            pkg.push_back(cTool.int8_view[0]);

            pkg = this->MBAP_header(pkg);

            oResponseLength = this->get_response_len(iType, iNumber);

            return pkg;
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


 private:       

        int slave_id;

        int k_PLC_ADDRESS_BASE;    

        int get_response_len(int fc, int data_len)
        {
            const int k_header_len = 9; // 9 = MBAP Header(7) + FC(1) + ByteFollow(1)
            switch (fc)
            {
            case 1:
            case 2:
                return k_header_len + ceil((double)data_len/8); 
                break;
            case 3:
            case 4:
                return k_header_len + data_len*2;
                break;
            case 5:
            case 6:
            case 15:
            case 16:
                return 12; // 12 = MBAP Header(7) + FC(1) + address(2) + numbuer or value(2)
                break;                    

            default:
                return -1; //沒有實作的Function Code
                break;
            }
        }

        std::vector<char> MBAP_header(std::vector<char> iPkg)
        {
            std::vector<char> pkg;

            // Transaction Identifier
            pkg.push_back(0x00);
            pkg.push_back(0x01);

            // Protocol Identifier
            pkg.push_back(0x00);
            pkg.push_back(0x00);

            // Message Length (X bytes to follow)
            tu_16 cTool;
            cTool.int16_view = iPkg.size() + 1;
            pkg.push_back(cTool.int8_view[1]);
            pkg.push_back(cTool.int8_view[0]);

            // slave id
            pkg.push_back(this->slave_id);

            // appening iPkg
            // https://stackoverflow.com/questions/2551775/appending-a-vector-to-a-vector
            pkg.insert(pkg.end(), iPkg.begin(), iPkg.end());

            return pkg;

        }

       // int WriteRequest
    };
} // namespace arc_modbus

#endif