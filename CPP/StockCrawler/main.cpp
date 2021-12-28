#include "YahooAPI.h"
#include <iostream>
#include <ctime>

#define PST 10

using namespace std;

int main(int argc, char* argv[])
{
    YahooAPI api; 

    time_t now = time(0);
    tm *gmtm = gmtime(&now);

    auto hour = gmtm->tm_hour+PST%24;

    std::cout << gmtm->tm_mday << " " << gmtm->tm_mon << std::endl;

    api.test("AA", "2020-01-01", "2020-01-01");

    //datatable::DataTable dt = api.get_ticker_data("spy", "2020-09-01", "2020-10-06");
    // datetime not supported in DataTables (https://github.com/anthonymorast/DataTables/issues/5)
    //dt.drop_columns(new string[1]{"Date"}, 1);  
    //dt.print_shape(cout);
    //dt.print_headers(cout);


    //api.download_ticker_data("qqq", "2020-01-01", "2020-10-07");

    //api.set_interval(MONTHLY);
    //datatable::DataTable dt2 = api.get_ticker_data("aapl", "2010-01-01", "2020-10-01", true);

    return 0;
}
