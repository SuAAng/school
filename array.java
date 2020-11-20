//입력한 단어가 txt 파일에 존재하는지 알려주는 프로그램(배열 이용)
import java.util.Scanner;
import java.util.StringTokenizer;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
public class array {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		
		
		try {

			FileReader fr = new FileReader(new File("test.txt"));
			
			char[] buffer = new char[100];
			String word = "";
			
			while(fr.read(buffer) != -1){
			word = word + String.valueOf(buffer);
			}


			String [] s;//단어 넣을 공간
			StringTokenizer tok = new StringTokenizer (word," \n");
			String [] tree;//트리구조로 단어 넣음
			String search;//서치할 단어
			int i = 0;
			int k = 0;
			int cmp;//2개 비교
		
			int n = tok.countTokens();//token 개수
			
			s = new String[n];
			tree = new String[1000000];
			
			for(i = 0; i<n; i++) {
				s[i]= tok.nextToken();
			}

			//트리 시작
			k = 0; i = 1;
			while (k < n) {

				if (tree[i] == null) {//tree가 비워져 있으면 채워넣기
					tree[i] = s[k];
					k++;
					i = 1;//넣고나서 다시 트리 1부터 보기	
				}
				else {
					cmp = tree[i].compareTo(s[k]);
					if (cmp < 0)//s[k]가 더 뒤에 있으면
					{
						i = (i * 2) + 1;
					
					}
					else if (cmp > 0) //s[k]가 더 앞에 있으면
					{
						i = i * 2;
					
					}
					else//이미 저장된 단어일 때
					{
						i = 1;// 다시 트리1부터 보기
						k++;
					}
				}	
			}
		
			
			//트리에 저장된 단어 찾기
			System.out.println("dkssud");
			while(true) {
				System.out.print("검색할 단어를 입력하시오(0입력 시 종료)>> ");
				search = scanner.next();
				if(search.compareTo("0") == 0) {
					System.out.print("종료");
					break;
				}	
				i = 1;
				while(true) {
					if (tree[i] == null) {
						System.out.println(search + "은/는 문서에 존재하지않습니다.");
						break;
					}	
					else if (tree[i].compareTo(search) == 0) {
						System.out.println(search + "은/는 문서에 존재합니다.");
						break;
					}
					else if (tree[i].compareTo(search) < 0) {
						i = (i * 2) + 1;
					}	
					else if (tree[i].compareTo(search) > 0) {
						i = i * 2;
					}	
			
				}
			}
			System.out.println(word);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
		e.printStackTrace();
		}
	}

}

