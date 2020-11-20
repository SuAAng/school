import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

class Write {
	//name이 0이면 링크 기록, 0이 아니면 노드 기록
	public void write(String log, int name) {
		try {
			String Path;//파일경로
			if(name == 0) {
				Path = "C:\\Users\\박수연\\Desktop\\log\\Link.txt";//링크 기록
			}
			else {
				Path =  String.format("C:\\Users\\박수연\\Desktop\\log\\Node" + name + ".txt");//노드 기록
			}
			
			BufferedWriter write = new BufferedWriter(new FileWriter(Path, true));

			write.write(log);
			write.close();

		} catch (IOException e) {
			System.out.println("파일 복사 error");
		}
	}
	
	// 시간 프린트 해주는 함수
	public void Time(int t, int name, String log) {
		int minute = (int) (t / 60000);
		int second = (int) ((t - minute*60000) / 1000);
		int msecond = t % 1000;

		String finalLog = String.format("%02d:%02d:%03d ", minute, second, msecond) + log + "\n";// 로그 시간
		
		
		write(finalLog, name);// 로그와 저장할 노드이름
	}
}

