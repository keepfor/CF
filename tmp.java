class Solution {
		public int maxCompatibilitySum(int[][] students, int[][] mentors) {
			int m = students.length, n = students[0].length;

			int[] s = new int[m];
			for(int i = 0;i < m;i++){
				for(int j = 0;j < n;j++){
					s[i] = s[i] * 2 + students[i][j];
				}
			}
			int[] t = new int[m];
			for(int i = 0;i < m;i++){
				for(int j = 0;j < n;j++){
					t[i] = t[i] * 2 + mentors[i][j];
				}
			}

			int max = 0;
			for(int[] a : new (m)){
				int sc = 0;
				for(int i = 0;i < m;i++){
					sc += n - Integer.bitCount(s[i] ^ t[a[i]]);
				}
				max = Math.max(max, sc);
			}
			return max;
		}

			public class IterablePermutation implements Iterable<int[]>, Iterator<int[]>
				{
					int[] a;
					boolean first = true;

					public IterablePermutation(int n) {
						assert n >= 1;
						a = new int[n];
						for(int i = 0;i < n;i++)a[i] = i;
					}

					public IterablePermutation(int... a) {
						this.a = Arrays.copyOf(a, a.length);
					}

					@Override
					public boolean hasNext() {
						if(first)return true;
						int n = a.length;
						int i;
						for(i = n - 2;i >= 0 && a[i] >= a[i+1];i--);
						return i != -1;
					}

					@Override
					public int[] next() {
						if(first) {
							first = false;
							return a;
						}
						int n = a.length;
						int i;
						for(i = n - 2;i >= 0 && a[i] >= a[i+1];i--);
						assert i != -1;
						int j;
						for(j = i + 1;j < n && a[i] < a[j];j++);
						int d = a[i]; a[i] = a[j - 1]; a[j - 1] = d;
						for(int p = i + 1, q = n - 1;p < q;p++,q--){
							d = a[p]; a[p] = a[q]; a[q] = d;
						}
						return a;
					}

					@Override
					public Iterator<int[]> iterator() {
						return this;
					}
				}
	}

