void func() {
    int n,k;

    cin>>n>>k;

    vector<int> v1,v2;

    for(int i=0;i<n/2;i++)
    {
        int x; cin>>x;
        v1.push_back(x);
    }

    for(int i=n/2;i<n;i++)
    {
        int x; cin>>x;
        v2.push_back(x);
    }

    map<int,int> mp;
    int n1 = n/2;
    int n2 = n - n/2;

    // Compute all subset sums for the first half
    for(int i=0;i<(1 << n1);i++)
    {  
        int st = i; 
        int x=0,y=0;
        while(st > 0)
        {
            if(st & 1) x += v1[y];
            y++;
            st>>=1; //right shift
        }

        mp[x]++;
    }

 
    int ans = 0;
    // Compute all subset sums for the second half and count valid pairs
    for (int i = 0; i < (1 << n2); i++) {  
        int st = i; 
        int x = 0, y = 0;
        while (st > 0) {
            if (st & 1) x += v2[y];
            y++;
            st >>= 1; // Right shift
        }

        if (mp.count(k - x)) {
            ans += mp[k - x];
        }
    }

    cout<<ans<<endl;
}