//입력한 단어가 txt 파일에 존재하는지 알려주는 프로그램(리스트 이용)

import java.util.Scanner;
import java.util.StringTokenizer;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

class ListNode{
	String data;
	ListNode Rlink;
	ListNode Llink;
	
	public ListNode(String data) {
		this.data = data;
		this.Rlink = null;
		this.Llink = null;
	}
}

class LinkedList{
	ListNode head = new ListNode(null);//헤드노드
	
	public ListNode create_node (String data) {
		ListNode new_node = new ListNode(data);
		
		return new_node;
	}

	public void insert_node (String data) {
		ListNode temp_node = head;//임시로 만들어 줌
		ListNode new_node = create_node(data);
		if (head.data == null) {//리스트에 아무것도 없을 때
			head = new_node;
		}
		
		else {
			while (true) {
				if (temp_node.data.compareTo(new_node.data) < 0) {//현재 노드보다 새 노드가 크면 오른쪽 링크로

					if (temp_node.Rlink == null) {
						temp_node.Rlink = new_node;
						break; //새 노드 연결 시켜주고 반복문 나옴
					}
					temp_node = temp_node.Rlink;
				}
				else if (temp_node.data.compareTo(new_node.data) > 0) {//현재 노드보다 새 노드가 크면 왼쪽 링크로
					if (temp_node.Llink == null) {
						temp_node.Llink = new_node;
						break; //새 노드 연결 시켜주고 반복문 나옴
					}
					temp_node = temp_node.Llink;
				}
				else {//이미 저장되어 있다면 저장 안함
					break;
				}
			}
		}	
	}
}

public class list {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		try {

			FileReader fr = new FileReader(new File("test.txt"));

			char[] buffer = new char[100];
			String word = "";
			
			while(fr.read(buffer) != -1){
			word = word + String.valueOf(buffer);
			}
			
		LinkedList link = new LinkedList();
		
		String [] s;//단어 넣을 공간
		StringTokenizer tok = new StringTokenizer(word," \n");//토큰
		String search;//서치할 단어
		int i = 0, k = 0;

		int n = tok.countTokens();//token 개수
		
		s = new String[n];
		
		for(i = 0; i < n; i++) {
			s[i]= tok.nextToken();
		}

		//리스트 넣기
		link.insert_node (s[0]); //트리의 맨 위에 넣어줌.
		
		k = 1;
		while (k < n) {
			link.insert_node (s[k]);
			k++;
		}
		//저장된 단어 찾기
		while(true){
			ListNode nlist = link.head;//검색할 때 쓰일 현재 리스트
			System.out.print("검색할 단어를 입력하시오(0입력 시 종료)>> ");
			search = scanner.next();
			if(search.compareTo("0") == 0) {
				System.out.print("종료");
				break;
			}
			while (true) {
				if (nlist == null) {
					System.out.println(search + "은/는 문서에 존재하지 않습니다.");
					break;
				}
				else if (nlist.data.compareTo(search) == 0) {
					System.out.println(search + "은/는 문서에 존재합니다.");
					break;
				}
				else if (nlist.data.compareTo(search) < 0) {
					nlist = nlist.Rlink;
				}
				else if (nlist.data.compareTo(search) > 0) {
					nlist = nlist.Llink;
				}
			}
		}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			} catch (IOException e) {
			e.printStackTrace();
			}
	}
		
}

	
