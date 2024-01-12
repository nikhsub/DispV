#ifndef CLUSTER
#define CLUSTER

#include <numeric>
#include <math.h>


class cluster {

  public:

  float Avg(std::vector<float> data){
     if(data.empty()) return -1;
     return std::accumulate(data.begin(), data.end(), 0.)/((float)data.size());
  }
  
  float AvgDistance(std::vector<float> data, float center){
     if(data.empty()) return -1;
     std::vector<float> tmp_data;
     tmp_data.clear();
     for(size_t i=0; i<data.size(); i++){
        tmp_data.push_back(fabs(data[i]-center)/center);
     }
     return std::accumulate(tmp_data.begin(), tmp_data.end(), 0.)/((float) tmp_data.size());
  }
  
  float RMS(std::vector<float> data, float center){
     if(data.empty()) return -1;
     std::vector<float> tmp_data;
     tmp_data.clear();
     for(size_t i=0; i<data.size(); i++){
        tmp_data.push_back(fabs(data[i]-center)/center);
     }
     return sqrt( std::inner_product(tmp_data.begin(), tmp_data.end(), tmp_data.begin(), 0.)/((float) tmp_data.size()) );
  }

  std::vector<float> bestcluster(std::vector<std::vector<float> > clusters, float target){
     float min = 1e10;
     std::vector<float> bestcluster;
     if(clusters.size()==0) return bestcluster;
     for(size_t i=0; i<clusters.size(); i++){
        if(clusters[i].size()<2) continue;
        float dist = AvgDistance(clusters[i], target);
        if(dist < min){
           min = dist;
           bestcluster = clusters[i];
        }
     }
     return bestcluster;
  }

  std::vector<std::vector<float> > clusters(std::vector<float> data, float limit){
     std::vector<std::vector<float> > clusters;
     std::sort(data.begin(), data.end(), camp);
     for(size_t i=0; i<data.size(); i++){
       std::vector<float> single(1,data[i]);
       clusters.push_back(single);
     }
     Join(clusters, limit);
     return clusters;

  }
  
  float Linkage(std::vector<float> A, std::vector<float> B){
     float max=0;
     for(size_t i=0; i<A.size();i++){
        for(size_t j=0; j<B.size();j++){
           float dist = fabs(A[i]-B[j]);
           if (dist>max) max=dist;
        }
     }
     
     return max;
  }
  
  void Join(std::vector<std::vector<float> > &obs, float limit){
     float min=1e10;
     std::pair<int, int> toJoin;
     for(int i=0; i<(int)(obs.size()-1); i++){
        for(int j=i+1; j<(int)obs.size(); j++){
           std::vector<float> obs1 = obs[i];
           std::vector<float> obs2 = obs[j];
           float distance = Linkage(obs1, obs2);
           if(distance<min){
              toJoin = std::pair<int, int>(i,j);
              min = distance;
           }
        }
     }
     if(min<limit){
        std::vector<float> new_obs = obs[toJoin.first];
        new_obs.insert(new_obs.end(), obs[toJoin.second].begin(), obs[toJoin.second].end());
        if(toJoin.first < toJoin.second){
           obs.erase(obs.begin()+toJoin.first);
           obs.erase(obs.begin()+toJoin.second-1);
        }
        
        else{
           obs.erase(obs.begin()+toJoin.first);
           obs.erase(obs.begin()+toJoin.second);
        }
        obs.push_back(new_obs);
        Join(obs,limit);          
     }
     else {
        return;
     }
  }

  static bool camp(float a, float b){
     return (a<b);
  }

};

#endif
