import java.util.Queue;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.PriorityQueue;
import java.util.Scanner;
import java.util.StringTokenizer;

public class map {

	public static void main(String[] args) {

		Scanner scanner = new Scanner(System.in);
		int line_num = 1;// 파일에서 몇 번째 줄인지 (파일 불러오기에서 사용)
		Graph g = new Graph(); // 그래프에 노드들 간의 가중치를 저장함
		double weight[] = new double[10001]; // 노드에 맞는 가중치의 합을 저장하는 배열 (가중치는 노드의 개수만큼) 약 1만 노드
		                                     //weight[1] = 마지막 노드가 1인
											 // 경로의 가중치의 합
		Path p[] = new Path[10001]; // 경로 저장할 배열, p[1]이면 노드 1이 마지막이 되는 경로
		                            //경로가 3개이면서 p[1]이면 path[2]에 노드1이 저장됨.
									// (노드개수만큼 필요)
		// ===========================================================================bfs알고리즘에만 필요한 것들
		PriorityQueue<Integer> q1 = new PriorityQueue<Integer>();
		PriorityQueue<Integer> q2 = new PriorityQueue<Integer>();
		int path_ok[] = new int[10001];// 경로에 추가되었는지 판단
		int q1In[] = new int[10001];// q1에 들어있는지 판단
		int q2In[] = new int[10001];// q2에 들어있는지 판단

		// ===========================================================================
		try {
			// ==================================================파일 불러와 graph에 저장시키기
			double a[] = new double[3];
			File file = new File("mapss.txt");// 파일불러오기
			FileReader filereader = new FileReader(file);
			BufferedReader bufReader = new BufferedReader(filereader);// 버퍼에 넣기

			while (line_num != 5001) { // 파일에 5000줄 존재
				String s = bufReader.readLine();// 1줄 불러오기
				int i = 0;
				StringTokenizer token = new StringTokenizer(s);// 토큰으로 자르기
				while (i != 3) {
					a[i] = Double.parseDouble(token.nextToken());// 3개로 나누기
					i++;
				}

				g.addGraph((int) a[0], (int) a[1], a[2]); // 자른거 Graph에 저장
				line_num++;// 다음줄 불러오기
			}
			// =====================================================================
			int alg = 0;
			while (alg != 3) {

				for (int i = 0; 10001 > i; i++) {
					weight[i] = 999; // 모든 노드의 처음 가중치는 999로 지정
				}
				for (int i = 0; 10001 > i; i++) {// 경유안했으면 0, 경유했으면 1
					path_ok[i] = 0;// 경유안했으면 0, 경유했으면 1
					q2In[i] = 0;// 안 들어있으면 0, 들어있으면 1
					q1In[i] = 0;// 안 들어있으면 0, 들어있으면 1
				}

				System.out.println("====================================");
				System.out.println("SSSP알고리즘으로 출력시 1입력 ");
				System.out.println("BFS알고리즘으로 출력시 2입력");
				System.out.print("종료시 3입력 -> ");
				alg = scanner.nextInt();// 무슨 알고리즘 사용할건지 입력

				if (alg == 1) {// SSSP알고리즘 이용
					// ==========================================
					System.out.println("====================================");
					System.out.println("<single source shortest path 알고리즘>");
					System.out.print("시작노드를 입력하시오.");
					int st = scanner.nextInt();// 시작 노드
					System.out.print("끝 노드를 입력하시오.");
					int fi = scanner.nextInt();// 끝 노드

					// =============================== 노드끼라 연결된 것을 찾아 weight에 저장시키면서 끝노드 찾기
					weight[st] = 0;// 첫 노드는 가중치가 0
					p[st] = new Path(); // 경로 생성
					p[st].setPath(st, 0); // 첫 번째 경로에 st 저장

					while (true) {// 끝노드를 찾을 때까지
						int next = 0;// 함수에서 가져올 다음 노드
						int connect = 0;// 연결할 노드
						for (int i = 1; i < 10001; i++) {//노드의 개수만큼 돌림
							next = g.nextNode(st, i);// 다음 노드를 가져옴

							if (next != 0) {// 연결할 노드가 존재할 때
								connect = next; // connect에 연결할 노드 저장
								if (weight[connect] == 999) {// connect가 처음으로 연결될 때
									p[connect] = new Path();// connect노드가 끝이 될 경로 생성
								}

								if (connect != 0 && weight[connect] != 1000) {// st와 연결된 곳이 있으면 connect는 0이 아님,
																			  // 경로로 쓰였던 노드는
																			  // 가중치가 1000으로 저장됨

									if (weight[connect] > weight[st] + g.getWeight(st, connect)) {// 원래 weight[connect]에
																								  // 저장된
																						   		  // 가중치보다 작으면
										weight[connect] = weight[st] + g.getWeight(st, connect);// 가중치의 합을 저장

										int j = 0;// 몇 번째 경로인지
										while (true) {// 경로 저장
											if (p[st].getPath(j) != 0) {// st의 j번째 배열에 경로가 저장되어 있으면
												p[connect].setPath(p[st].getPath(j), j);// st의 j번째 경로에 저장되어있는 노드를
																						// connect의 j번째 경로에 저장
												j++;
											} else {
												p[connect].setPath(connect, j);// 마지막 경로배열에 connect를 저장
												break;
											}
										}
									}
								}
							}
						}

						weight[st] = 1000; // 경로로 썼던 노드는 가중치를 1000으로 놓아 못쓰게 만든다

						for (int i = 0; 10001 > i; i++) {// 썼던 노드를 제외한 나머지 노드들 중 가중치의 합이 제일 작은 것을 선택
							if (weight[st] >= weight[i]) {
								st = i;
							}
						}
						if (weight[st] == 999) {// 연결되지 않아 가중치가 999인 노드가 제일 작은 가중치일 때 도달 불가능
							System.out.println("도달 불가능");
							break;
						}
						if (st == fi) {// 연결되다가 최종적으로 끝노드와 연결이 되면
							System.out.print("최종 경로:");
							int j = 0;//추가되는 경로의 개수
							while (true) {// 경로 출력
								if (p[fi].getPath(j) != 0) {
									System.out.print(p[fi].getPath(j) + "->");
									j++;
								} else {
									System.out.println("경로 끝!");
									j--;
									break;
								}
							}
							double wsum = j - weight[fi];// 가중치의 합
							System.out.println("가중치의 합: " + wsum); // 가중치의 합을 출력

							break;
						}
					}

				}
				// ==================================================================
				if (alg == 2) {// BFS알고리즘 이용
					System.out.println("====================================");
					System.out.println("<BFS 알고리즘>");
					System.out.print("시작노드를 입력하시오.");
					int st = scanner.nextInt();// 시작 노드
					System.out.print("끝 노드를 입력하시오.");
					int fi = scanner.nextInt();// 끝 노드

					// ==============================================================
					q1.offer(st);// q1에 st를 집어넣음
					weight[st] = 0;// st의 가중치의 합은 0
					q1In[st] = 1;// q1에 st가 들어감
					p[st] = new Path(); // st의 경로 생성
					p[st].setPath(st, 0); // st경로의 첫 번째 경로에 st 저장

					while (q1.isEmpty() == false || q2.isEmpty() == false) {// q1과 q2 모두 들어간 노드가 없을 때까지

						// ===========================================================
						// q1을 내보내면서 q2에 노드 집어넣는 과정
						while (q1.isEmpty() != true) {//q1에 있는 값이 없어질 때까지
							int now_node = q1.poll();//q1에서 현재 노드를 나오게 함
							path_ok[now_node] = 1;//경로에 들어갔음을 의미함
							for (int i = 0; i < 10001; i++) {
								int next_node = g.nextNode(now_node, i);//현재 노드와 연결된 노드 next_node에 저장
								if (next_node != 0 && path_ok[next_node] == 0 && q1In[next_node] == 0) {//현재 노드와 연결된 노드가 있고,
																										//경로에 들어간 적이 없으며
																										//q1에 들어간 적이 없을 때
									double now_weight = weight[now_node] + g.getWeight(now_node, next_node);//now_node와 next_node간의 가중치를
																											//now_node의  가중치의 합과 더해
																											//next_node의 가중치의 합에 저장함
									if (weight[next_node] > now_weight) {//원래 저장되어있던 next_node 가중치의 합보다 방금 더한 next_node
																		 //가중치의 합이 더 작으면
										weight[next_node] = now_weight;//가중치의 합을 작은 값으로 다시 저장
										if (q2In[next_node] == 0) {//q2에 한 번도 들어간 적이 없을 때
											q2.offer(next_node);//q2에 연결되는 노드를 집어넣음
											q2In[next_node] = 1;//q2에 들어갔음을 의미함
											p[next_node] = new Path();//새로운 경로 생성
										}
										int j = 0;//j번째 경로
										while (true) {//경로 저장
											if (p[now_node].getPath(j) != 0) {//now_node의 경로 배열에 경로가 저장되어 있을 때까지
												p[next_node].setPath(p[now_node].getPath(j), j);//connect의 경로에 j번째 경로에
																								//st의 j번째 경로에 저장되어있는 
												                                                //노드를 저장
												j++;
											} else {
												p[next_node].setPath(next_node, j);
												break;
											}
										}
									}
								}
							}
						}
						// ==================================================================
						//q2을 내보내면서 q1에 노드 집어넣는 과정
						while (q2.isEmpty() != true) {// q2에 있는 값이 없어질 때까지
							int now_node = q2.poll();// 현재 노드를 나오게 함
							path_ok[now_node] = 1;
							for (int i = 0; i < 10001; i++) {
								int next_node = g.nextNode(now_node, i);// 현재 노드와 연결된 노드 next_node에 저장
								if (next_node != 0 && path_ok[next_node] == 0 && q2In[next_node] == 0) {//현재 노드와 연결된 노드가 있고,
																										//경로에 들어간 적이 없으며
																										//q2에 들어간 적이 없을 때

									double now_weight = weight[now_node] + g.getWeight(now_node, next_node);//now_node와 next_node간의 가중치를
																											//now_node의  가중치의 합과 더해
																								     		//next_node의 가중치의 합에 저장함
									if (weight[next_node] > now_weight) {// 현재 저장되어있는 가중치의 합보다 지금 경로의 가중치의 합이 더 작으면
										weight[next_node] = now_weight;// 가중치의 합을 작은 값으로 다시 저장
										if (q1In[next_node] == 0) {
											q1.offer(next_node);// q2에 연결되는 노드를 집어넣음
											q1In[next_node] = 1;
											p[next_node] = new Path();

										}
										int j = 0;
										while (true) {// 경로 저장
											if (p[now_node].getPath(j) != 0) {// now_node의 경로 배열에 경로가 저장되어 있을 때까지
												p[next_node].setPath(p[now_node].getPath(j), j);// connect의 경로에 j번째 경로에
																								// st의 j번째 경로에
																								// 저장되어있는 노드를 저장
												j++;
											} else {
												p[next_node].setPath(next_node, j);
												break;
											}
										}
									}
								}
							}
						}
						// ==================================================================
					}
					if (weight[fi] != 999) {
						int j = 0;
						System.out.print("최종 경로: ");
						while (true) {// 최종 경로

							if (p[fi].getPath(j) != 0) {
								System.out.print(p[fi].getPath(j) + "->");
								j++;
							} else {
								System.out.println("경로 끝!");
								j--;
								break;
							}
						}
						double wsum = j - weight[fi];// 가중치의 합
						System.out.println("가중치의 합: " + wsum); //경로의 개수-weight[fi]
					} else {
						System.out.println("도달 불가능");
					}
				}
			}
			System.out.println("종료합니다...");
		} catch (FileNotFoundException e) {
		} catch (IOException e) {
			System.out.println(e);
		}
	}
}

class Graph {// 다익스트라 알고리즘 사용할 때
	double distance[][];

	public Graph() {
		distance = new double[10001][10001]; // a와 b는 노드를 뜻함[10001][10001]
	}

	public void addGraph(int a, int b, double weight) {// 가중치 저장하는 함수
		distance[a][b] = 1 - weight;
		distance[b][a] = 1 - weight;
	}

	public double getWeight(int a, int b) {// 가중치 불러오는 함수
		return distance[a][b];
	}

	public int nextNode(int a, int b) {
		int c = 0; // nextnode가 없을 때, 0이 나오게 되어 있으니까 0이 나오면 도달 불가능 출력!

		if (distance[a][b] != 0) {
			c = b;
		}

		return c;
	}
}

class Path {// 경로 저장
	int path[];

	public Path() {
		path = new int[10000];
	}

	public int getPath(int i) {// 만약 1->3->7 경로라면 노드 1은 path[0]에 1이 저장, 노드 3는 노드 1의 getPath(0)을 사용해 노드3의
								// path[0]에 1을 저장하고, path[1]에 3를 저장, 노드 7은 노드 3의 getPath(0), getPath(1) 이용해서
								// path[0], path[1] 저장하고 path[2]에 자기꺼 저장
		return path[i];
	}

	public void setPath(int node, int i) {
		path[i] = node;
	}
}
