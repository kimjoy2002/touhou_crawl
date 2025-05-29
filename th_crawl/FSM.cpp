//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: FSM.cpp
//
// 내용: fsm클래스 정의
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "FSM.h"

FSMstate::FSMstate(monster_state id_):
NumofTran(0), id(id_)
{
	trans.reserve(32);
}

void FSMstate::AddTransition(monster_state_input input_, monster_state after_)
{
	trans.push_back(state_trans_infor(input_,after_));
	NumofTran++;
}
void FSMstate::DelTransition(monster_state_input input_)
{
	vector<state_trans_infor>::iterator it;
	for(it = trans.begin(); it!=trans.end() ; it++)
	{
		if((*it).input == input_)
		{
			trans.erase(it);
			return;
		}
	}
}

monster_state FSMstate::Transition(monster_state_input input_)
{
	vector<state_trans_infor>::iterator it;
	for(it = trans.begin(); it!=trans.end() ; it++)
	{
		if((*it).input == input_)
		{ 
			return (*it).after;
		}
	}
	return id;
}

FSMclass::FSMclass(monster_state current_state_):
current_state(current_state_)
{
}

void FSMclass::AddState(FSMstate* Newstate_)
{
	map<monster_state,FSMstate*>::iterator it;

	if(!state_map.empty()) //이미 존재하는 상태인경우
	{
		it = state_map.find(Newstate_->GetId());
		if(it != state_map.end())
			return;
	}

	state_map.insert(pair<monster_state,FSMstate*>(Newstate_->GetId(),Newstate_));
}

void FSMclass::DeleteState(monster_state state_)
{
	map<monster_state,FSMstate*>::iterator it;

	if(!state_map.empty()) //존재하는 경우
	{
		it = state_map.find(state_);
		if(it != state_map.end())
		{
			state_map.erase(it);
		}
	}
}


monster_state FSMclass::StateTransition(monster_state_input input_)
{	
	if(!current_state)
		return MS_ERROR;


	map<monster_state,FSMstate*>::iterator it;

	if(!state_map.empty()) //존재하는 경우
	{
		it = state_map.find(current_state);
		if(it != state_map.end())
		{
			FSMstate *pState = (FSMstate*)((*it).second);
			current_state = pState->Transition(input_);
			return current_state;
		}
	}
	return MS_ERROR;
}



//아래부터 상태
FSMstate state_normal(MS_NORMAL);
FSMstate state_sleep(MS_SLEEP);
FSMstate state_atack(MS_ATACK);
FSMstate state_rest(MS_REST);
FSMstate state_follow(MS_FOLLOW);
FSMstate state_find(MS_FIND);
FSMstate state_wait(MS_WAIT);
FSMstate state_decide(MS_DECIDE);


void init_state()
{
	state_normal = FSMstate(MS_NORMAL);
	state_sleep = FSMstate(MS_SLEEP);
	state_atack = FSMstate(MS_ATACK);
	state_rest = FSMstate(MS_REST);
	state_follow = FSMstate(MS_FOLLOW);
	state_find = FSMstate(MS_FIND);
	state_wait = FSMstate(MS_WAIT);
	state_decide = FSMstate(MS_DECIDE);


	//상태 노말: 적을 발견하지않고 떠도는 상태
	state_normal.AddTransition(MSI_FOUND,MS_ATACK);
	state_normal.AddTransition(MSI_ATACKED,MS_ATACK);
	state_normal.AddTransition(MSI_NOISE,MS_ATACK);
	state_normal.AddTransition(MSI_REST,MS_REST);
	state_normal.AddTransition(MSI_SEARCH, MS_FIND);
	state_normal.AddTransition(MSI_FOLLOW, MS_FOLLOW);
	
	//상태 수면: 한 자리에서 자는 상태
	state_sleep.AddTransition(MSI_NOISE,MS_ATACK);
	state_sleep.AddTransition(MSI_ATACKED,MS_ATACK);
	state_sleep.AddTransition(MSI_FOUND,MS_ATACK);
	state_sleep.AddTransition(MSI_WAKE,MS_NORMAL);

	//상태 공격: 목표를 잡음
	state_atack.AddTransition(MSI_LOST,MS_NORMAL);
	state_atack.AddTransition(MSI_REST,MS_NORMAL);
	state_atack.AddTransition(MSI_SEARCH, MS_FIND);
	
	//상태 휴식: 휴식중
	state_rest.AddTransition(MSI_ATACKED,MS_ATACK);
	state_rest.AddTransition(MSI_NOISE,MS_ATACK);
	state_rest.AddTransition(MSI_FOUND,MS_ATACK);
	state_rest.AddTransition(MSI_REST,MS_SLEEP);
	state_rest.AddTransition(MSI_WAKE,MS_NORMAL);

	//상태 추종: 동맹이 플레이어를 따라감
	state_follow.AddTransition(MSI_ATACKED,MS_ATACK);
	state_follow.AddTransition(MSI_LOST,MS_NORMAL);
	state_follow.AddTransition(MSI_FOUND,MS_ATACK);
	state_follow.AddTransition(MSI_SEARCH,MS_FIND);
	
	//상태 탐색: 특정 위치로 이동하는 기능
	state_find.AddTransition(MSI_ATACKED, MS_ATACK);
	state_find.AddTransition(MSI_FOUND, MS_ATACK);
	state_find.AddTransition(MSI_LOST, MS_NORMAL);
	state_find.AddTransition(MSI_REST, MS_NORMAL);
	state_find.AddTransition(MSI_FOLLOW, MS_FOLLOW);

	//상태 대기: (주로) 동맹이 자신의 위치를 지키면서 주변 몹들을 정리하는 상태
	state_wait.AddTransition(MSI_ATACKED, MS_ATACK);
	state_wait.AddTransition(MSI_SEARCH, MS_FIND);
	state_wait.AddTransition(MSI_FOLLOW, MS_FOLLOW);
	
	//상태 지정된 경로: 슈팅 스프린트 전용 ai. 정해진 경로로만 이동하면서 마법을 씀
	//전이 없음
}

void base_state_setup(FSMclass& state, monster_state first_state)
{
	state.AddState(&state_normal);
	state.AddState(&state_sleep);
	state.AddState(&state_atack);
	state.AddState(&state_rest);
	state.AddState(&state_follow);
	state.AddState(&state_find);
	state.AddState(&state_wait);
	state.AddState(&state_decide);

	state.SetState(first_state);
}