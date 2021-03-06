#ifndef METRO_H
#define METRO_H
//#include"HeadFile.h"
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <fstream>
#include <iostream> // for std::cout
#include <utility> // for std::pair
#include <algorithm> // for std::for_each
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <string>
using namespace std;
using namespace boost;
typedef property<edge_weight_t, int> EdgeWeightProperty;
typedef boost::adjacency_list<listS, vecS, undirectedS, no_property, EdgeWeightProperty >MetroGraph;
typedef MetroGraph::edge_descriptor Edge;
typedef graph_traits<MetroGraph>::vertex_descriptor Vertex;
typedef property_map<MetroGraph, vertex_index_t>::type VertexMap;


typedef struct graph_station
{
  int sysid;
  int line; //位于哪一线路
  int id;
} Sstation;

typedef struct station
{

  int id;
  string name;
  bool istransfer; //是不是换乘站
  int position_x, position_y;
  //int line; //存放所属线路的编号
  vector<Sstation> TransferID;//从0编号
}Station;

typedef struct path
{
  int len; //经过的站点数量
  vector<int> stnid; //途经站点的id
} Path;


class SearchSys
{
private:
  int sta_num;
  int sys_id;
  int line_num;
  MetroGraph mtgph; //站点线路图
  MetroGraph all_pairs_shorest_graph;
  vector<Station> station_list; //站点列表，从0编号
  vector<Sstation> graph_station_list; //系统站点列表，从0编号
  vector<vector<int> > Line_list;//二维变长数组记录每个路线的站点信息
  vector<vector<Vertex>*> dijkstra_tree_list; //存储最小生成树
  static map<string, int> Line_nameToNum;//站点名字到id的映射
  static map<string, int> Sta_nameToNum;//线路名到id的映射
  int Same_Sta_weight;//换乘的cost
  void get_all_pairs_shorest_graph();
  Path find_spath(Vertex src, Vertex trg);
public:
  SearchSys(const string& city, int trans_cost);
  ~SearchSys();
  //int Init_gph(const string& city); //从文件中加载图信息
  int Init_gph(const string& city); //从文件中加载图信息
  int Store_gph(const string& city); //将图信息保存到文件
  Path Find_the_shrt_path(const string& start_station, const string& end_station);  //寻找两个站点之间的最短路
  Path Trave_metro(const string& src_station);  //全遍历
  Path Find_line_with_name(const string& linename); //根据线路名称查询线路站点
  void print_path(Path& p);  //打印某条线路上的站点序列
  void save_path(Path& p, const string& filename);
  void save_path(Path *&p, const string& filename, int path_num);
  int Find_line(const string& station_name, Path* &line_list);
};
#endif
