#include <bayesian_webclass/http_downloader.h>
#include <boost/filesystem.hpp>
#include "utilities.cpp"
#include <map>
#include <string>
int main(){
//	HTTPDownloader downloader;
//
//    //get html addresses from textfile to vector of string
//    std::vector<std::string> addresses = downloader.get_urls_from_file("html/http_addresses.txt");
//    std::string html_text,filename;
//    std::string path_root("output/");
//    int count = 1;
//
//    boost::filesystem::create_directories ("output"); //create a directory for results
//
//    for (std::string i : addresses)
//    {
//
//    	html_text = downloader.download(i); //for every link from file download the html code
//    	filename = path_root + "kod_html" + std::to_string(count) + ".txt";
//    	downloader.write_str_to_file(filename, html_text);
//    	html_text = downloader.cleanhtml(html_text); //clean downloaded html code
//    	filename = path_root + "kod_html" + std::to_string(count) + "_clean.txt";
//    	downloader.write_str_to_file(filename, html_text);
//    	std::string output_of_parsing;
//
//    	//false is you want to save output of parsing in string, else if you want to save it in file ,set true, and not set last parameter
//    	downloader.parse_html_and_save(html_text, "/html/body", count, false, output_of_parsing);  //parse html_text and save to file in /output directory text from "html/body" node, that means only the text between <body></body>
//
//      	std::cout << output_of_parsing <<std::endl; //outputs to the console result of parsing
//      	count++;
//
//    }
    std::unique_ptr<HTTPDownloader> ptr_http(new HTTPDownloader());
    std::map<int,std::string> id_domain_map(tokenizeCsv());
    int i = 0;
    std::map<int,std::string>::iterator map_it;
    bool is_downloadable = true;
    int good_links = 0,all_links = 0; //counter of usable links
//    for ( i = 0, map_it= id_domain_map.begin(); i<30; ++i,++map_it)
    for (map_it= id_domain_map.begin(); map_it!=id_domain_map.end(); ++map_it)
    {
        all_links++;
        std::cout << map_it->first << "=>" << map_it->second;
        ptr_http->download(map_it->second,is_downloadable);
        if (is_downloadable)
        {
            std::cout << "<== IS GOOOD" << std::endl;
            ++good_links;
        }
        is_downloadable = true; //renew flag
        std::cout << all_links << std::endl;
    }
    double prc = good_links/(double)all_links;
    prc = prc*100;
    std::cout << "All links: " << all_links << "\nGood links: " << good_links << "\nPercentage: " << prc << "%" << std::endl;
    return 0;
}