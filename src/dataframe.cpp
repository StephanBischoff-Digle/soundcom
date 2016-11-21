#include "dataframe.h"

void Dataframe::setData(const std::string &data) {
  std::vector<char> intermediateData(data.begin(), data.end());
  for (size_t i = 0; i < intermediateData.size(); i++) {
    char current = intermediateData[i];
    for (auto k = 0; k < 8; k++) {
      if ((current >> k & 1) == 1)
        data_.push_back(true);
      else
        data_.push_back(false);
    }
  }
}
