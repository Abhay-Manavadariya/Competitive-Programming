#include<bits/stdc++.h>
using namespace std;

class DisjointSet{
    vector<int> rank,parent,size;

public:
    DisjointSet(int n)
    {
        rank.resize(n+1,0); //1 - based index
        parent.resize(n+1);
        size.resize(n+1,1);

        for(int i=0;i<=n;i++)
        {
            parent[i] = i;
        }
    }

    int findUltimateParent(int node)
    {
        if(node == parent[node])
        {
            return node;
        }

        return parent[node] = findUltimateParent(parent[node]);
    }

    void unionByRank(int u,int v)
    {
        int ulp_u = findUltimateParent(u);
        int ulp_v = findUltimateParent(v);

        if(ulp_u == ulp_v)
        {
            return;
        }

        //smaller attach to larger
        if(rank[ulp_u] < rank[ulp_v])
        {
            parent[ulp_u] = ulp_v;
        }
        else if(rank[ulp_u] > rank[ulp_v])
        {
            parent[ulp_v] = ulp_u;
        }
        else{
            //if rank same then definitely rank will increased.

            parent[ulp_v] = ulp_u; // you can do vice versa. parent[ulp_u] = ulp_v;
            //here ulp_v attach to ulp_u so rank will increased of ulp_u.
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u,int v)
    {
        int ulp_u = findUltimateParent(u);
        int ulp_v = findUltimateParent(v);

        if(ulp_u == ulp_v)
        {
            return;
        }

        if(size[ulp_u] < size[ulp_v]){
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else
        {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

int spanningTree(int V, vector<pair<int,pair<int,int>>> edges)
{
    sort(edges.begin(),edges.end()); //sort according to weight
    
    DisjointSet dsu(V);

    int minWeight = 0;

    for(auto it : edges)
    {
        int wt = it.first;
        int u = it.second.first;
        int v = it.second.second;
        
        if(dsu.findUltimateParent(u) != dsu.findUltimateParent(v))
        {
            minWeight += wt;
            dsu.unionBySize(u,v);
        }
    }
    
    return minWeight;
}

int main()
{

#ifndef ONLINE_JUDGE 
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    int V = 3;
    vector<pair<int,pair<int,int>>> edges;
    edges.push_back({5,{0,1}});
    edges.push_back({3,{1,2}});
    edges.push_back({1,{0,2}});

    cout<<spanningTree(V,edges)<<"\n";
    return 0;
}