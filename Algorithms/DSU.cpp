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

int main()
{

#ifndef ONLINE_JUDGE 
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    DisjointSet ds(7);
    ds.unionBySize(1,2);
    ds.unionBySize(2,3);
    ds.unionBySize(4,5);
    ds.unionBySize(6,7);
    ds.unionBySize(5,6);

    //check if 3 and 7 belong to same component or not.
    if(ds.findUltimateParent(3) == ds.findUltimateParent(7))
    {
        cout<<"Before (3,7)  :- YES"<<"\n";
    }
    else
    {
        cout<<"Before (3,7)  :- NO"<<"\n";
    }

    ds.unionBySize(3,7);

    if(ds.findUltimateParent(3) == ds.findUltimateParent(7))
    {
        cout<<"After (3,7)  :- YES"<<"\n";
    }
    else
    {
        cout<<"After (3,7)  :- NO"<<"\n";
    }


    
    return 0;
}