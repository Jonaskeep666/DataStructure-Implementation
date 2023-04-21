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

    // Phase 2：當 queue 為空，表示 Spanning Tree 繪製完成
    while(!heap.isEmpty()){
        u = heap.DeleteMin()    // 從 heap Pop出最小值(有最小成本邊的點)
        // 找出所有 點u 的鄰近點v
        for each v G:Adj[u]{
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