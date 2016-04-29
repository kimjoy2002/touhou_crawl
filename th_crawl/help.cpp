//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: help.cpp
//
// 내용: 도움말
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "environment.h"
#include "display.h"
#include "key.h"
#include "note.h"


extern HANDLE mutx;
extern display_manager DisplayManager;


void Help_Show()
{
	deletesub();

	bool loop_ = true;
	int input_;
	WaitForSingleObject(mutx, INFINITE);
	printsub("<동방 크롤 도움말 목록>",true,CL_normal);
	printsub("",true,CL_normal);
	printsub("?. 커맨드",true,CL_normal);
	printsub(":. 진행 노트",true,CL_normal);
	printsub("0. 스토리",true,CL_normal);
	changedisplay(DT_SUB_TEXT);
	ReleaseMutex(mutx);
	while(loop_)
	{
		input_ = waitkeyinput(true);
		switch(input_)
		{
		case '?':
			WaitForSingleObject(mutx, INFINITE);
			deletesub();
			printsub("                                   --- 커맨드 목록 ---",true,CL_normal);
			printsub("",true,CL_normal);
			printsub("<이동>                                             <마법>",true,CL_normal);
			printsub("방향키 - 다음의 키가 서로 동일하다                 M - 마법 기억",true,CL_normal);
			printsub("↖↑↗    1 2 3    y k u                           Z - 마법 사용",true,CL_normal);
			printsub("←·→ <> 4 5 6 <> h . l                           z - 빠른 마법 사용(현재 차이없음)",true,CL_normal);
			printsub("↙↓↘    7 8 9    b j n                           I - 기억하고있는 마법 확인",true,CL_normal);
			printsub("o   - 자동탐색                                     ",true,CL_normal);
			printsub("                                                   <캐릭터 정보 출력>",true,CL_normal);
			printsub("<던전의 탐색>                                      @ - 간단한 캐릭터 상태",true,CL_normal);
			printsub("5      - 100턴 휴식                                $ - 현재 가지고 있는 돈(미구현)",true,CL_normal);
			printsub("x      - 근처 조사                                 % - 자세한 캐릭터 정보",true,CL_normal);
			printsub("s또는. - 1턴 넘기기                                ^ - 신앙 정보",true,CL_normal);
			printsub("X      - 맵을 조사                                 \\ - 식별된 아이템 정보",true,CL_normal);
			printsub("<,>    - 계단 오르기/내려가기                      A - 캐릭터 특성 확인",true,CL_normal);
			printsub("O,C    - 문 열기/닫기                              [ - 입고있는 장비 표시",true,CL_normal);
			printsub("ctrl-O - 던전 정보(미구현)                         } - 현재 무기 표시",true,CL_normal);
			printsub("                                                   \" - 현재 장신구 표시",true,CL_normal);
			printsub("<아이템관련>                                       E - 경험치 표시",true,CL_normal);
			printsub("i      - 가지고 있는 아이템                        m - 스킬창 표시",true,CL_normal);
			printsub("g또는, - 떨어져있는 아이템줍기                     ",true,CL_normal);
			printsub("d      - 아이템버리기                              ",true,CL_normal);
			printsub("D      - 가장 최근에 얻은 아이템버리기             <비게임 커맨드>",true,CL_normal);
			printsub("e      - 먹기(음식)                                ctrl-P - 지난 메세지 보기",true,CL_normal);
			printsub("r      - 읽기(두루마리,책)                         S - 세이브후 종료",true,CL_normal);
			printsub("q      - 마시기(물약)                              ctrl-S - 세이브후 종료(경고없음)",true,CL_normal);
			printsub("f/F    - 빠른/선택 던지기                          ctrl-Q - 세이브없이 종료",true,CL_normal);
			printsub("v      - 스펠카드 사용	                             # - 게임 덤프하기",true,CL_normal);
			printsub("V      - 스펠카드 사용                          ",true,CL_normal);
			printsub("w      - 무기장착( - 키로 맨손)                    ",true,CL_normal);
			printsub("W/T    - 방어구 장착/해제                          ",true,CL_normal);
			printsub("P/R    - 장신구 장착/해제                          ",true,CL_normal);
			printsub("ctrl-A - 자동줍기 활성/해제                        ",true,CL_normal);
			printsub("                                                   ",true,CL_normal);
			printsub("<능력 관련>                                        ",true,CL_normal);
			printsub("c - 없음                                           ",true,CL_normal);
			printsub("p - 기도                                           ",true,CL_normal);
			changedisplay(DT_SUB_TEXT);
			ReleaseMutex(mutx);
			break;
		case ':':
			{	
				WaitForSingleObject(mutx, INFINITE);
				deletesub();
				char temp[300];
				sprintf_s(temp,300,"%8s|%-18s|%s\n","턴","장소","내용");
				printsub(temp,true,CL_normal);
				for(list<note_dummy>::iterator it = save_note.note_list.begin(); it != save_note.note_list.end(); it++)
				{
					sprintf_s(temp,300,"%8d|%-18s|%s",it->turn,it->place.c_str(),it->text.c_str());
					printsub(temp,true,it->color);
				}
				changedisplay(DT_SUB_TEXT);
				ReleaseMutex(mutx);	
				while(1)
				{
					switch(waitkeyinput(true))
					{
					case VK_UP:
						changemove(1);  //위
						continue;
					case VK_DOWN:
						changemove(-1); //아래
						continue;
					case VK_PRIOR:
						changemove(DisplayManager.log_length);
						continue;
					case VK_NEXT:
						changemove(-DisplayManager.log_length);
						continue;
					case VK_ESCAPE:
						loop_ = false;
						break;
					default:
						continue;
					}
					break;
				}
			}
			break;
		case '0':
			WaitForSingleObject(mutx, INFINITE);
			deletesub();
			printsub("                                    --- 스토리 ---",true,CL_normal);
			printsub("환상향이 던전화되어버렸다!",true,CL_normal);
			printsub("",true,CL_normal);
			printsub("환상향의 인요들은 순간적인 상황변화를 받아들이지 못하고 곳곳에서 격한 반응을 보였다. ",true,CL_normal);
			printsub("",true,CL_normal);
			printsub("당신은 환상향을 원래대로 되돌려놓기위해 던전을 탐험하도록 시작했다. ",true,CL_normal);
			changedisplay(DT_SUB_TEXT);
			ReleaseMutex(mutx);
			break;
		//case '1':
		//	WaitForSingleObject(mutx, INFINITE);
		//	deletesub();
		//	printsub("                                   --- 제작자 잡담 ---",true,CL_normal);
		//	printsub("본게임은 던전크롤(스톤수프)와 동방프로젝트를 섞은 게임입니다.",true,CL_normal);
		//	printsub("",true,CL_normal);
		//	printsub("제작자 - joy1999",true,CL_normal);
		//	printsub("",true,CL_normal);
		//	printsub("제작툴 - Visual C++ 2008 Express Edition",true,CL_normal);
		//	printsub("",true,CL_normal);
		//	printsub("제작언어 - C++(다이렉트X 9.0)",true,CL_normal);
		//	printsub("",true,CL_normal);
		//	printsub("제작기간 - 모름",true,CL_normal);
		//	printsub("",true,CL_normal);
		//	printsub("",true,CL_normal);
		//	printsub("잡담: 이번 게임은 묻히지 않았으면 좋겠다.",true,CL_normal);
		//	printsub("",true,CL_normal);
		//	printsub("혹시 게임에 관련된 건의사항, 질문, 버그등에대해서 말하시고 싶으신게 있다면 다음의 블로그 주소로 와주세요.",true,CL_normal);
		//	printsub("",true,CL_normal);
		//	printsub("http://joy1999.egloos.com/",true,CL_normal);
		//	printsub("",true,CL_normal);
		//	printsub("",true,CL_normal);
		//	printsub("감사합니다.",true,CL_normal);
		//	printsub("",true,CL_normal);
		//	changedisplay(DT_SUB_TEXT);
		//	ReleaseMutex(mutx);
		//	break;
		//case '2':
		//	WaitForSingleObject(mutx, INFINITE);
		//	deletesub();
		//	printsub("                                   --- 도움주신 분들 ---",true,CL_normal);
		//	printsub("게임을 만드는데 많은 도움을 주신 이하의 분들에게 모두 감사드립니다.",true,CL_normal);
		//	printsub("",true,CL_normal);
		//	printsub("",true,CL_normal);
		//	printsub("<테스터>",true,CL_normal);
		//	printsub("이소리스크, 디인, 녹색이슬, Rian☆iku, 후쟈, Minacle, Zeroize, 카나땅",true,CL_normal); 
		//	printsub("TachibanaMiya, 미오, Dhin, 레나ㅹ, 나가토, mystery, 준범, 어떤",true,CL_normal);
		//	printsub("",true,CL_normal);
		//	printsub("",true,CL_normal);
		//	printsub("<특히 많은 도움을 주신분들>",true,CL_normal);
		//	printsub("",true,CL_help);
		//	printsub("이소리스크 - 많은 기획을 도와주심.",true,CL_normal);
		//	printsub("",true,CL_help);
		//	printsub("디인님 - 역시 기획쪽으로도 많이 도와주심. 도트도 몇개 찍어주심.",true,CL_normal);
		//	printsub("",true,CL_help);
		//	printsub("Rian☆iku - 제가 자주 설호함.",true,CL_normal);
		//	printsub("",true,CL_help);
		//	printsub("미오, 녹색이슬 - 이번에 크롤 토너먼트 같이 나감.",true,CL_normal);
		//	printsub("",true,CL_help);
		//	printsub("그외의 #동방입천칙, #동방크롤 채널 분들 모두 추가적으로 감사드림.",true,CL_normal);
		//	printsub("",true,CL_normal);
		//	printsub("그리고 지금 다운받아서 플레이하신 분들 모두 사랑함.",true,CL_normal);
		//	printsub("",true,CL_normal);
		//	printsub("테스터하시고싶으신 분들은 블로그에 남기세요. 크롤러 우대, 버그 잘 찾는분 우대.",true,CL_normal);
		//	changedisplay(DT_SUB_TEXT);
		//	ReleaseMutex(mutx);
		//	break;
	/*	case '3':
			WaitForSingleObject(mutx, INFINITE);
			deletesub();
			changedisplay(DT_SUB_TEXT);
			printsub("                                   --- 자체 F A Q ---",true,CL_normal);
			printsub("Q. 고를 수 있는 신과 신앙심을 얻는 방법은?",true,CL_help);
			printsub("   A. 카나코, 에이린, 뱌쿠렌뿐입니다.",true,CL_normal);
			printsub("      카나코- 몹을 죽인다. P템위에서 기도한다.",true,CL_normal);
			printsub("      에이린- 맹물을 제외한 포션을 마신다. 포션위에서 기도한다. P템위에서 기도한다.",true,CL_normal);
			printsub("      뱌쿠렌- 남은 스킬 경험치로 마법스킬을 수련한다.",true,CL_normal);
			printsub("",true,CL_normal);
			printsub("Q. 왜 인간과 무녀를 안골라도 레이무지?",true,CL_help);
			printsub("   A. 도트 우려먹다보니까 그렇습니다. 다음 버젼에선 종족에 맞게 도트가 바뀝니다.",true,CL_normal);
			printsub("",true,CL_normal);
			printsub("Q. 동방캐릭터는 플레이어캐릭터로 플레이할 수 없게될 예정?",true,CL_help);
			printsub("   A. 아닙니다.",true,CL_normal);
			printsub("",true,CL_normal);
			printsub("Q. 매크로가 없다. ctrl-G가 없다. 오른쪽에 인벤창이 없다. 등등",true,CL_help);
			printsub("   A. 아직 크롤에 비해서 부족한 점은 점차 추가해나갈 예정입니다.",true,CL_normal);
			printsub("",true,CL_help);
			printsub("Q. 마법성공률이 너무 정확하게 나온다.",true,CL_help);
			printsub("   A. 후에 성공률은 좋음, 나쁨, 보통같은 문장으로 바꿀 예정입니다.",true,CL_normal);
			printsub("",true,CL_help);
			printsub("Q. 굶어죽겠는데 음식이 없다!",true,CL_help);
			printsub("   A. 배고픈 상태에선 c를 눌러서 p를 한칸 소모하여 허기를 채울 수 있습니다.",true,CL_normal);
			printsub("",true,CL_help);
			printsub("Q. 스킬 성장치를 보고 싶다.",true,CL_help);
			printsub("   A. 블로그에 공개중입니다. 게임상에서는 m키로 스킬경험치를 보는 화면에서 !를 누르면 성장치로 바뀝니다.",true,CL_normal);
			printsub("",true,CL_help);
			printsub("Q. 이 게임에 목표는 뭐지?",true,CL_help);
			printsub("   A. 아직 미완성이라 별다른 목표는 없지만 이번 버젼에선 요괴의산 막층의 쪽지를 가져와야합니다.",true,CL_normal);
			printsub("",true,CL_help);
			printsub("Q. 서브던전의 계단이 다른계단과 구별하기 힘들다.",true,CL_help);
			printsub("   A. 후에 도트를 바꿀 예정입니다. 현재는 층에서 내려가는 계단이 4개 이상일때",true,CL_normal);
			printsub("      그 중 하나가 서브던전 계단이라고 보시면됩니다.",true,CL_normal);
			printsub("      만약 아무리 찾아도 없으면 버그니 신고해주세요.",true,CL_normal);
			printsub("",true,CL_help);
			printsub("Q. 타이틀 이미지를 2개 이상 받으면 어떻게 할거지?",true,CL_help);
			printsub("   A. 타이틀 이미지를 여러개받으면 실행할때마다 랜덤한 타이틀을 출력할겁니다.",true,CL_normal);
			printsub("",true,CL_help);
			printsub("Q. 타이틀을 만들어주고 싶다. 도트를 찍어주고 싶다. 테스트를 해주고 싶다.",true,CL_help);
			printsub("   A. 아얄씨 #동방크롤 채널로 오세요.",true,CL_normal);
			printsub("",true,CL_help);
			changedisplay(DT_SUB_TEXT);
			ReleaseMutex(mutx);
			break;*/
		case VK_ESCAPE:
			loop_ = false;
			break;
		default:
			break;
		}

	}
		

	changedisplay(DT_GAME);
}

