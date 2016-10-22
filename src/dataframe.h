#pragma once

#include <string>
#include <vector>

class Dataframe {
private:
    std::vector<bool> data_;
    
    
public:
    
    void setData(const std::string& data);
    const std::vector<bool>& getDataFrame() const {return data_;}
};
