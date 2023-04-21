BFS(G, s){
    // 初始化設定
    for each vertex u ∈ G.V - {s} {
        u.color = WHITE     // 點u 未被拜訪過
        u.d = ∞             // 起點s 到 點u 的距離 = ∞(目前沒有路徑)
        u.π = -1            // 點u 的前一點(父點) 未知
    }
    // Phase 1：先拜訪 起點s
    s.color = GRAY          // 起點s 已拜訪過
    s.d = 0                 // 起點s 到自己 的距離 = 0
    s.π = -1                // 起點s 的前一點(父點) 未知

    // 建立 Queue 並將 起點s 放入隊中
    Queue q
    q.Push(s)

    // Phase 2：當 queue 為空，表示 所有的點 皆以拜訪完畢
    while(!q.isEmpty()){
        u = q.Pop()
        // Phase 2-1：找 點u 「所有」未拜訪的 鄰近點v
        for each v ∈ G.Adj[u]{
            if (v.color == WHITE){
                v.color = GRAY  // 已拜訪 點v，但未完成(所有鄰點結束)
                v.d = u.d + 1   // 點v 是 點u 的 鄰點，故距離+1
                v.π = u         // 點v 是由 點u 走來
                q.Push(v)
            }
        }
        u.color = BLACK
    }
}

DFS(G){
    // 初始化設定
    for each vertex u ∈ G.V{
        u.color = WHITE // 點u 未被拜訪過
        u.π = -1        // 點u 的前一點(父點) 未知
    }
    time = 0            // 時間從0開始

    // 任選一「未拜訪 點u」為起點 執行DFS
    for each vertex u ∈ G.V{
        if(u.color == WHITE)
            DFSVisit(G, u)
    }
}

DFSVisit(G, u){
    // Phase 1：先拜訪 起點u
    time = time + 1 // 紀錄 拜訪起點的時間 = 總時間+1
    u.d = time      // 紀錄在 點u 的「發現時間」
    u.color = GRAY  // 點u 已拜訪，但未完成(所有鄰點結束)

    // Phase 2-1：找 點u 未拜訪的鄰近點v
    for each v ∈ G:Adj[u]{
        if(v.color == WHITE){
            v.π = u         // 點v 是由 點u 走來
            DFSVisit(G, v)  // 以「點v」為起點 執行DFS
        }
    }

    // Phase 2-2：若 點u「沒有」未拜訪的鄰近點，表示 點u 已拜訪 且 完成
    u.color = BLACK     // 點u 已拜訪 且 完成
    time = time + 1     // 紀錄 完成 點u 的時間 = 總時間+1
    u.f = time
}

bool DFSVisit(G, u){
    // Phase 1：先拜訪 起點u
    time = time + 1 // 紀錄 拜訪起點的時間 = 總時間+1
    u.d = time      // 紀錄在 點u 的「發現時間」
    u.color = GRAY  // 點u 已拜訪，但未完成(所有鄰點結束)

    // Phase 2-1：找 點u 未拜訪的鄰近點v
    for each v ∈ G:Adj[u]{
        if(v.color == WHITE){
            v.π = u         // 點v 是由 點u 走來
            DFSVisit(G, v)  // 以「點v」為起點 執行DFS
        }
        // For 有向圖：指向 灰色點v(前輩)，即為Back Edge
        // For 無向圖：指向 非父點 之灰色點v(前輩)，即為Back Edge
        if(v.color == GRAY && u.π!=v)
            return true;
    }

    // Phase 2-2：若 點u「沒有」未拜訪的鄰近點，表示 點u 已拜訪 且 完成
    u.color = BLACK     // 點u 已拜訪 且 完成
    time = time + 1     // 紀錄 完成 點u 的時間 = 總時間+1
    u.f = time
}

MST_Prims(G, W, r){ // W:紀錄「邊成本」的集合，、r是起點
    // 初始化設定
    for each vertex u ∈ G.V {
        u.key = ∞           // 點u.Key = 周圍最小成本邊的「成本值」
        u.π = -1            // 點u 的前一點(父點) 未知
    }

    // Phase 1：建立 Heap
    r.key = 0;
    heap.Create(G.V)    // 將每個頂點的Key值，放入heap中

    // Phase 2：當 heap 為空，表示 Spanning Tree 繪製完成
    while(!heap.isEmpty()){
        u = heap.DeleteMin()    // 從 heap Pop出最小值(有最小成本邊的點)
        // 找出所有 點u 的鄰近點v
        for each v ∈ G:Adj[u]{
            // 若 點v 還在heap中(尚未加入 Spanning Tree)
            // 且 Edge(u,v) 的成本 < 點v 周圍其他邊的成本
            if( v ∈ heap && W(u,v) < v.key){
                v.π = u         // 將 點u->點v
                v.key = w(u,v)  // 將 點v 所存的最小邊成本 改為 Edge(u,v) 的成本
                heap.adjust(v)  // 以 點v 為起點，調整 heap
            }
        }
    }
}

SP_Dijkstra(G,w,s){
    // 初始化設定
    for each vertex u ∈ G.V {
        sp[V] = 0    // 所有點的 最短路徑 皆未決定
        V.d = ∞      // 所有點的 最短路徑長 初始=大數 
        V.π = -1
    }
    s.d = 0             // 起點s 的最短距離=0(就是自己，最先被 Pop出來)
    heap.Create(G.V)    // 將每個頂點的dist值，放入heap中 

     while(!heap.isEmpty()){
        u = heap.DeleteMin()    // 從 heap Pop出最小值(有最小dist的點)
        sp[u] = 1                // 點u 的 (起點->點u)最短距離 已決定
        // 找出所有 點u 的鄰近點v
        for each v ∈ G:Adj[u]{
            if(v.d > u.d + w(u,v)){ // 若 (s->v)的距離 > (s->u->v)的距離
                v.d = u.d + w(u,v)  // 則 更新 起點s->點v 的最短距離
                v.π = u             // 將 點u->點v
                heap.adjust(v)      // 以 點v 為起點，調整 heap
            }
        }
    }
}

SP_BellmanFord(G,w,s){
    for i=1 to n 
        Dist[i] = cost[s][i] // 初始化 Dist[i]= 起點s 只走一步 到i 的 距離

    // 更新 Dist[i] 從 k=2～k=n-1，(k從2開始，是因為 k=1 在初始化時 已完成)
    for k=2 to n-1 {
        for u=1 to n {  // 更新 Disk^k[u]；u=1～n

            // 有向圖中，存在 點u->點v 的邊(一種 點u 的相鄰點= 點v 的概念，外加 邊由u->v)
            // 表示 可經過 點u 到 點v，Dist[v]可能更短
            for each v ∈ (u,v) { 
                //  若 (s->u->v) < (s->v)，則 更新 Dist[v]=Dist[u]+cost[u][v]
                if(Dist[v]>(Dist[u]+cost[u][v]))
                    Dist[v] = Dist[u]+cost[u][v]
            }
        }
    }
    // 至此 照理說已完成 最短路徑規劃，以下是 BellmanFord 獨有的「檢查負Cycle」
    // 作法：在完成最短路徑規劃後，照理說，所有的 Dist[i] ≤ Dist[u]+cost[u][i]
    //      若發現 有 Dist[i] > Dist[u]+cost[u][i] 表示「存在負迴路」，可使路徑長-∞
     for i=1 to n {
        if(Dist[v]>(Dist[u]+cost[u][v]))
            negCycle = 1 // 存在負迴路
     }
}

SP_Floyed(G,w){
    // 初始化 A^0[i][j] = w(i,j)
    for i=1 to n
        for j=1 to n
            A[i][j] = w(i,j)

    // 計算 A^1～A^n
    for k=1 to n
        for i=1 to n
            for j=1 to n {
                if(A[i][j]>A[i][k]+A[k][j])
                    A[i][j] = A[i][k]+A[k][j]
            }
}

A(G,w){
    // 將 Adjacency Matrix 的結果 存入 A+ Matrix
    for i=1 to n
        for j=1 to n
            A+[i][j] = w(i,j)
    // 若 有 i->k & k->j 則存在 i->j，此稱為「遞移性質」
    for k=1 to n
        for i=1 to n
            for j=1 to n {
                A+[i][j] = ( A+[i][j] || (A+[i][k] && A+[k][j]) ) // 任一成立 即成立
                A*[i][j] = ( A+[i][j] || (A+[i][k] && A+[k][j]) || (i==j) )
            }
}