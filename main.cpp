
// vincentlaucsb-csv-parser
#include "csv.hpp"


#include <iostream>
#include <vector>
#include <sstream>


std::vector<std::string> samples = {
    // timestamp
    "Date,Open,High,Low,Close,Volume,Adj Close\n"
    "2017-02-24,64.529999,64.800003,64.139999,64.620003,21705200,64.620003\n"
    "2017-02-23,64.419998,64.730003,64.190002,64.620003,20235200,64.620003\n"
    "2017-02-22,64.330002,64.389999,64.050003,64.360001,19259700,64.360001\n"
    "2017-02-21,64.610001,64.949997,64.449997,64.489998,19384900,64.489998\n"
    "2017-02-17,64.470001,64.690002,64.300003,64.620003,21234600,64.620003\n",

    // basic
    "foo, bar, you\n"
    "3.3, 3.7, 3.8\n"
    "4.3, 4.7, 4.8\n",
    
    // quoted header
    "\"foo\", bar, you\n"
    "3.3, 3.7, 3.8\n"
    "4.3, 4.7, 4.8\n",
    
    // ; separator
    "foo; bar; you\n"
    "3.3; 3.7; 3.8\n"
    "4.3; 4.7; 4.8\n",
    
    // ; separator, french numerical separator
    "foo; bar; you\n"
    "3,3; 3,7; 3,8\n"
    "4,3; 4,7; 4,8\n"
    
};


int main()
{
  
  for(unsigned k = 1; k < samples.size(); ++ k)
  {
    std::stringstream sstream(samples[k]);

    csv::CSVFormat format;
    format.trim({ ' ', '\t'  });
    if (k == 3 || k== 4)
        format.delimiter({';'});
    // format.delimiter({';', ','});
    // format.header_row(0);
    csv::CSVReader reader(sstream, format);
    
    std::vector<std::string> names(reader.get_col_names());
    for(unsigned i = 0; i < names.size(); ++ i)
      std::cout << names[i]<<", ";
    std::cout << std::endl;
    for (csv::CSVRow& row: reader) { // Input iterator
      for (csv::CSVField& field: row) {
          // By default, get<>() produces a std::string.
          // A more efficient get<string_view>() is also available, where the resulting
          // string_view is valid as long as the parent CSVRow is alive
          if (k<4)
            std::cout << field.get<double>();
          else
          {
            long double value;
            bool ok = field.try_parse_decimal(value, ',');
            if (ok)
              std::cout << value;
            else
              std::cout << "?";
          }
          std::cout << ",";
      }
      std::cout << std::endl;
    }
  
    
    std::cout << "---------------------------------------"<<std::endl;
  }


  return 0;
}