#include "HostsFileParser.h"

HostsFileParser::HostsFileParser()
{
    //ctor
}

HostsFileParser::HostsFileParser(const std::string& file)
{
    m_fp.open(file);
    m_open = m_fp.is_open();
    parse();
}


bool HostsFileParser::parse(){
    std::array<char,1024> line{};
    if(!m_open){
        std::cerr << "hosts file not opened\n";
        return false;
    }
    int ctr=0;
    std::regex uncommented_line("^([0-9\\.]+)[ \\t]+([^\\s]+).*");
    do{
        std::fill(line.begin(),line.end(),0);
        m_fp.getline((char*)&line[0],1024);
        std::string tmp_line = (char*)&line[0];
        tmp_line = trim(tmp_line);
        std::smatch base_match;
    std::cout << "r1";
        std::cout << tmp_line << "\n";
        if(ctr++ == 20){
            system("pause");
            ctr =0;
        }
        if(std::regex_search(tmp_line,base_match,uncommented_line)){
            if(base_match.size() >= 2){
                m_entries.insert(std::make_pair<const char*,const char*>(base_match[1].str().c_str(),base_match[2].str().c_str()));
            }
        }
        std::cout << "r2";
    }while(!m_fp.eof() && m_fp.good());
}
HostsFileParser::~HostsFileParser()
{
    //dtor
    if(m_fp.is_open())
        m_fp.close();

}
