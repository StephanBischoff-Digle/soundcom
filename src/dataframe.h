#pragma once

#include <string>
#include <vector>

class Dataframe {
private:
    std::vector<bool> data_;
    
    
public:
    
    void setData(const std::string& data);
    //void setBinaryData(const std::vector<bool>& data);
    const std::vector<bool>& getDataFrame() const {return data_;}
    //const std::string& getData();
};
