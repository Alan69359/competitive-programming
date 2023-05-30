void dfs1(int u, int father, int dep)
{
    depth[u] = dep, fa[u] = father, trsize[u] = 1;
    for (int i = he[u]; ~i; i = ne[i])
    {
        int j = no[i];
        if (j == father) continue;
        dfs1(j, u, dep + 1);
        trsize[u] += trsize[j];
        if (trsize[son[u]] < trsize[j]) son[u] = j;
    }
}

void dfs2(int u, int par)
{
    id[u] = ++ cnt, nwe[cnt] = we[u], p[u] = par;
    if (!son[u]) return;
    dfs2(son[u], par);
    for (int i = he[u]; ~i; i = ne[i])
    {
        int j = no[i];
        if (j == fa[u] || j == son[u]) continue;
        dfs2(j, j);
    }
}

void updatepath(int u, int v, int k)
{
    while (p[u] != p[v])
    {
        if (depth[p[u]] < depth[p[v]]) swap(u, v);
        modifyseq(1, id[p[u]], id[u], k);
        u = fa[p[u]];
    }
    if (depth[u] < depth[v]) swap(u, v);
    modifyseq(1, id[v], id[u], k);
}

ll querypath(int u, int v)
{
    ll res = 0;
    while (p[u] != p[v])
    {
        if (depth[p[u]] < depth[p[v]]) swap(u, v);
        res += querysum(1, id[p[u]], id[u]);
        u = fa[p[u]];
    }
    if (depth[u] < depth[v]) swap(u, v);
    res += querysum(1, id[v], id[u]);
    return res;
}

void updatetree(int u, int k)
{
    modifyseq(1, id[u], id[u] + trsize[u] - 1, k);
}

ll querytree(int u)
{
    return querysum(1, id[u], id[u] + trsize[u] - 1);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &we[i]);
    memset(he, -1, sizeof he);
    for (int i = 0; i < n - 1; i ++ )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }
    dfs1(1, -1, 1);
    dfs2(1, 1);   
}
