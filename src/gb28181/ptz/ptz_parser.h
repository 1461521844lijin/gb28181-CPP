/*
**	********************************************************************************
**
**	File		: ptz_parser.h
**	Description	: 
**	Modify		: 2020/3/2		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once

#include <string>
#include "defs.h"

namespace GB28181
{
    


using namespace std;




class PtzParser
{
public:
    PtzParser() = default;
    ~PtzParser() = default;

    int ParseControlCmd(control_cmd_t &ctrlcmd, const string &cmdstr);

private:
    void parse_ptz(const char *b, control_cmd_t &ctrlcmd);
    void parse_fi(const char *b, control_cmd_t &ctrlcmd);
    void parse_preset(const char *b, control_cmd_t &ctrlcmd);
    void parse_patrol(const char *b, control_cmd_t &ctrlcmd);
    void parse_scan(const char *b, control_cmd_t &ctrlcmd);

private:
    uint8_t m_b4;
    uint8_t m_b5;
    uint8_t m_b6;
    uint8_t m_b7;
};

} // namespace GB281


