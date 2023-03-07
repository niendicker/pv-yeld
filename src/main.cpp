// Edit : rewritten for cURLpp 0.7.3
// Note : namespace changed, was cURLpp in 0.7.2 ...

#include <cURLpp.hpp>
#include <Options.hpp>

// RAII cleanup

curlpp::Cleanup myCleanup;

// Send request and get a result.
// Here I use a shortcut to get it in a string stream ...
int main(int argc, char** argv){

std::ostringstream os;
os << curlpp::options::Url(std::string("http://example.com"));

string asAskedInQuestion = os.str();
};