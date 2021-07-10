	class Solution {
		public int waysToBuildRooms(int[] par) {
			int[][] g = parentToG(par);
			int n = par.length;
			int[][] pars = parents(g, 0);

			final int mod = 1000000007;
			int[] ord = pars[1];
			int[][] fif = enumFIF(200000, mod);
			int[] des = new int[n];
			long ans = 1;
			for(int i = n-1;i >= 0;i--){
				int cur = ord[i];
				des[cur]++;
				for(int e : g[cur]){
					if(par[cur] == e)continue;
					des[cur] += des[e];
					ans = ans * fif[1][des[e]] % mod;
				}
				ans = ans * fif[0][des[cur]-1] % mod;
			}
			return (int)ans;
		}


		public int[][] enumFIF(int n, int mod) {
			int[] f = new int[n + 1];
			int[] invf = new int[n + 1];
			f[0] = 1;
			for (int i = 1; i <= n; i++) {
				f[i] = (int) ((long) f[i - 1] * i % mod);
			}
			long a = f[n];
			long b = mod;
			long p = 1, q = 0;
			while (b > 0) {
				long c = a / b;
				long d;
				d = a;
				a = b;
				b = d % b;
				d = p;
				p = q;
				q = d - c * q;
			}
			invf[n] = (int) (p < 0 ? p + mod : p);
			for (int i = n - 1; i >= 0; i--) {
				invf[i] = (int) ((long) invf[i + 1] * (i + 1) % mod);
			}
			return new int[][]{f, invf};
		}


		int[][] parents(int[][] g, int root) {
			int n = g.length;
			int[] par = new int[n];
			Arrays.fill(par, -1);

			int[] depth = new int[n];
			depth[0] = 0;

			int[] q = new int[n];
			q[0] = root;
			for (int p = 0, r = 1; p < r; p++) {
				int cur = q[p];
				for (int nex : g[cur]) {
					if (par[cur] != nex) {
						q[r++] = nex;
						par[nex] = cur;
						depth[nex] = depth[cur] + 1;
					}
				}
			}
			return new int[][]{par, q, depth};
		}


		public int[][] parentToG(int[] par)
		{
			int n = par.length;
			int[] ct = new int[n];
			for(int i = 0;i < n;i++){
				if(par[i] >= 0){
					ct[i]++;
					ct[par[i]]++;
				}
			}
			int[][] g = new int[n][];
			for(int i = 0;i < n;i++){
				g[i] = new int[ct[i]];
			}
			for(int i = 0;i < n;i++){
				if(par[i] >= 0){
					g[par[i]][--ct[par[i]]] = i;
					g[i][--ct[i]] = par[i];
				}
			}
			return g;
		}

	}