#include "cache.h"
#include "log.h"

std::string getCurrTime(){
  time_t curtime;
  struct tm* loc_time;
  curtime = time(NULL);
  loc_time = localtime(&curtime);
  char* curr = asctime(loc_time);

  printf("getLoctime is:%s\n", curr);
  std::string ans(curr);
  //char* time = ( char* ) malloc(strlen(curr)+1);
  //memset(time, '\0', strlen(curr)+1);
  //strcpy(time, curr);
  return ans;
}

double timeDiff(std::string date1){
  struct tm c;
  std::string curr1 = getCurrTime();
  const char *curr = curr1.c_str();
  strptime(curr, "%a, %b %d %H:%M:%S %Y", &c);

  struct tm d;
  const char *date = date1.c_str();
  strptime(date, "%a, %d %b %Y %H:%M:%S GMT", &d);
  time_t date_t = mktime(&d);
  time_t curr_t = mktime(&c);
  double diff = difftime(curr_t, date_t);

  printf("curr - date in seconds is: %f\n", diff);

  return diff;
}

std::vector<char> checkCache(requestHead head, int uid, FILE* file){
  std::vector<char> ans;
  //  int status;
  if(cache.find(head.get_path()) == cache.end()){
    //status = 1;
    printf("not in cache");

  }else{

    //responseHead
    std::string date = cache[head.get_path()].get_date();
    if(timeDiff(date) > EXPIRE_TIME){
      //status = 2;
      printf("in cache, but expired at EXPIREDTIME");

    }
    //still need to test validation
    else{
      //      status = 4;
      printf("in cache, valid");
      ans = cache[head.get_path()].get_body();
    }
  }
  //  logCheckRequest(file, uid, status);

  return ans;
}

int allcocCache(std::string url, responseHead head){
  std::string cacheControl = head.get_cache();
  int status = 2;
  if(cacheControl.find("no-cache") != std::string::npos||
     cacheControl.find("no-store") != std::string::npos){
    status = 1;
    return status;
  }
  cache[url] = head;

  if(cacheControl.find("must-revalidate") != std::string::npos){
    status = 3;
    cache[url] = head;
    return status;
  }

  return status;
}                    

int main(){
  getCurrTime();
}
