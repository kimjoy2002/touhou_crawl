//
//
//void map_algorithms01(int num)
//{
//	vector<map_dummy*> vec_map;
//	vector<int> special_enter;
//	calcul_spe_enter(num,special_enter);
//	
//
//	vec_map.reserve(32);
//
//
//	
//
//	int rand_dummy = rand_int(20,30);
//	for(int i=0;i<rand_dummy;i++) //rand_dummy만큼의 맵더미를 생산
//	{
//		int repeat = 10;
//		int pattern_ = 0;
//		bool special_ = false;
//		if(!special_enter.empty())
//		{
//			special_ = true;
//			repeat = 99999;//특수패턴은 (거의)무한반복시킴
//			pattern_ = special_enter.back();
//			special_enter.pop_back();
//		}
//		for(int j=0;j<repeat;j++) //무한반복 제거용
//		{
//			bool success= true;
//			int r_size_x = rand_int(3,8);
//			int r_size_y = rand_int(3,8);
//			int m_size=5;
//			coord_def temp_coord(randA(DG_MAX_X-(r_size_x+2)*2-1-m_size*2)+r_size_x+2+m_size,randA(DG_MAX_Y-(r_size_y+2)*2-1-m_size*2)+r_size_y+2+m_size);		
//			map_dummy* temp = new map_dummy(temp_coord, true,r_size_x,r_size_y, pattern_); //랜덤한 맵더미
//			
//			vector<map_dummy*>::iterator it;
//			for (it=vec_map.begin();it!=vec_map.end();it++) 
//			{
//				if((*it)->collution(temp_coord,r_size_x,r_size_y) || (*it)->plus_collution(temp_coord,r_size_x,r_size_y)) //맵더미충돌시엔 만들지 않음
//				{
//					success = false;
//					break;
//				}
//			}	
//			if(success) //겹치지 않을때 맵더미푸쉬
//			{
//				vec_map.push_back(temp);
//				break;
//			}
//			else
//			{
//				delete temp; //겹치면 메모리 해제하고 다시 맵더미 생성
//				continue;
//			}
//		}
//	}
//
//	vector<map_dummy*>::iterator it;
//	for(it=vec_map.begin();it!=vec_map.end();it++)  //방들을 마스크주기
//		(*it)->mask(env[num]);
//
//	stack<coord_def> path_stack;
//
//	map_dummy* temp = vec_map.back();
//	for(it=vec_map.begin();it!=vec_map.end();it++) 
//	{
//		if(PathSearch(temp->GetEntrance(),(*it)->GetExit(),path_stack,ST_MAP,num))//방에 걸린 마스크를 피해서 경로저장
//		{
//			(*it)->SetConnectExit(true);
//			temp->SetConnectEnter(true);
//		}
//		temp = (*it);
//	}
//
//	{
//		vector<map_dummy*>::iterator it2 = vec_map.begin();
//		for(it=vec_map.begin();it!=vec_map.end();it++)  //연결이 안된 방들을 다시 연결시도
//		{
//			for(;!(*it)->GetConnect() && it2 != vec_map.end();it2++)
//			{
//				if(it == it2)
//					continue;
//				if(PathSearch((*it)->GetEntrance(),(*it2)->GetExit(),path_stack,ST_MAP,num))//방에 걸린 마스크를 피해서 경로저장
//				{
//					(*it)->SetConnectEnter(true);
//					temp->SetConnectExit(true);
//				}				
//			}
//		}
//	}
//
//
//	for(int i = 0;i<DG_MAX_X;i++)
//		for(int j = 0;j<DG_MAX_Y;j++)
//			env[num].dgtile[i][j].tile = DG_WALL; //다시 전부 벽으로
//
//
//	while(!path_stack.empty())
//	{
//		coord_def path_temp = path_stack.top();
//		env[num].dgtile[path_temp.x][path_temp.y].tile = DG_FLOOR; //저장한 도로를 칠하기
//		path_stack.pop();
//	}
//
//	int percent_ = randA(10);
//	for(it=vec_map.begin();it!=vec_map.end();it++) 
//	{//방을 만든다.
//		(*it)->make_map(env[num]);
//		if(!(*it)->pattern && randA(10)>=percent_)
//			(*it)->make_door(env[num]);
//	}
//
//	for (it=vec_map.begin();it!=vec_map.end();it++)
//		delete *it;
//
//	for(int i=0;i<6;i++)
//	{
//		while(1)
//		{
//			int x = randA(DG_MAX_X-1),y=randA(DG_MAX_Y-1);
//			if(env[num].dgtile[x][y].tile == DG_FLOOR  && !(env[num].dgtile[x][y].flag & FLAG_NO_MONSTER) )
//			{
//				if(i>2)
//				{
//					env[num].stair_up[i-3].x = x;
//					env[num].stair_up[i-3].y = y;
//					env[num].dgtile[x][y].tile = DG_UP_STAIR;
//				}
//				else
//				{
//					env[num].stair_down[i].x = x;
//					env[num].stair_down[i].y = y;
//					env[num].dgtile[x][y].tile = DG_DOWN_STAIR;	
//				}
//				break;
//			}
//		}
//	}
//}
//void map_algorithms02(int num, int piece)
//{
//	vector<map_dummy*> vec_map;
//	vector<map_dummy*> vec_special_map;
//	vector<int> special_enter;
//	calcul_spe_enter(num,special_enter);
//
//	int prev_x=0;
//	int prev_y=0;
//	int step = 0;
//
//	int rand_dummy = special_enter.size();
//	for(int i=0;i<rand_dummy;i++) //rand_dummy만큼의 맵더미를 생산
//	{	
//		int repeat = 10;
//		int pattern_ = 1;
//		bool special_ = false;
//		if(!special_enter.empty())
//		{
//			special_ = true;
//			repeat = 99999;//특수패턴은 (거의)무한반복시킴
//			pattern_ = special_enter.back();
//			special_enter.pop_back();
//		}
//		for(int j=0;j<repeat;j++) //무한반복 제거용
//		{
//			bool success= true;
//			int r_size_x = rand_int(2+piece/3,4+piece/3);
//			int r_size_y = rand_int(2+piece/3,4+piece/3);
//			int m_size=5;
//			coord_def temp_coord(randA(DG_MAX_X-(6+2)*2-1-m_size*2)+6+2+m_size,randA(DG_MAX_Y-(6+2)*2-1-m_size*2)+6+2+m_size);		
//			map_dummy* temp = new map_dummy(temp_coord, false,r_size_x,r_size_y,pattern_); //랜덤한 맵더미
//			
//			vector<map_dummy*>::iterator it;
//			for (it=vec_special_map.begin();it!=vec_special_map.end();it++) 
//			{
//				if((*it)->collution(temp_coord,r_size_x,r_size_y) || (*it)->plus_collution(temp_coord,r_size_x,r_size_y)) //맵더미충돌시엔 만들지 않음
//				{
//					success = false;
//					break;
//				}
//			}		
//			if(success) //겹치지 않을때 맵더미푸쉬
//			{
//				vec_special_map.push_back(temp);
//				break;
//			}
//			else
//			{
//				delete temp; //겹치면 메모리 해제하고 다시 맵더미 생성
//				continue;
//			}
//		}
//	}
//
//
//	for(int i=0;i<25-piece;i++)
//	{
//		int j=0;
//		for(;j<20;j++) //무한반복 제거용
//		{
//			bool success= true;
//			int next_x=0,next_y=0;
//			int r_size_x = rand_int(1+piece/3,4+piece/3);
//			int r_size_y = rand_int(1+piece/3,4+piece/3);
//			int m_size=5;
//			if(step != 1)
//				next_x = randA(DG_MAX_X-(r_size_x+2)*2-1-m_size*2)+r_size_x+2+m_size;
//			else
//				next_x = prev_x+rand_int(-r_size_x+1,r_size_x-1);
//
//			if(step != -1)
//				next_y = randA(DG_MAX_Y-(r_size_y+2)*2-1-m_size*2)+r_size_y+2+m_size;
//			else
//				next_y = prev_y+rand_int(-r_size_y+1,r_size_y-1);
//
//			coord_def temp_coord(next_x,next_y);		
//			map_dummy* temp = new map_dummy(temp_coord, false,r_size_x,r_size_y,0); //랜덤한 맵더미
//
//			if(step)
//			{
//				if(step == 1)
//				{
//					temp->SetEnter(coord_def(next_x,prev_y>next_y?next_y+r_size_y-1:next_y-r_size_y+1));
//				}
//				else
//				{
//					temp->SetEnter(coord_def(prev_x>next_x?next_x+r_size_x-1:next_x-r_size_x+1,next_y));
//				}
//			}
//
//			
//			vector<map_dummy*>::iterator it;
//			if(piece < 4+randA(3))
//			{
//				for (it=vec_map.begin();it!=vec_map.end();it++) 
//				{
//					if((*it)->collution(temp_coord,r_size_x,r_size_y) || (*it)->plus_collution(temp_coord,r_size_x,r_size_y)) //맵더미충돌시엔 만들지 않음
//					{
//						success = false;
//						break;
//					}
//				}
//			}
//			for (it=vec_special_map.begin();it!=vec_special_map.end();it++) 
//			{
//				if((*it)->collution(temp_coord,r_size_x,r_size_y) || (*it)->plus_collution(temp_coord,r_size_x,r_size_y)) //맵더미충돌시엔 만들지 않음
//				{
//					success = false;
//					break;
//				}
//			}
//			if(success) //겹치지 않을때 맵더미푸쉬
//			{
//				step = (step!=-1)?-1:1;
//				prev_x = next_x+rand_int(-r_size_x+1,r_size_x-1);
//				prev_y = next_y+rand_int(-r_size_y+1,r_size_y-1);
//				temp->SetExit(coord_def(prev_x,prev_y));
//				vec_map.push_back(temp);
//				break;
//			}
//			else
//			{
//				delete temp; //겹치면 메모리 해제하고 다시 맵더미 생성
//				continue;
//			}
//		}
//		if(j==0)
//		{
//			step = 0;	
//		}
//	}
//
//	vector<map_dummy*>::iterator it;
//	for(it=vec_special_map.begin();it!=vec_special_map.end();it++)  //방들을 마스크주기
//		(*it)->mask(env[num]);
//
//
//	stack<coord_def> path_stack;
//	map_dummy* temp = vec_map.back();
//	
//	for(it=vec_special_map.begin();it!=vec_special_map.end();it++) 
//	{
//		if(PathSearch(temp->GetEntrance(),(*it)->GetExit(),path_stack,ST_MAP,num))//방에 걸린 마스크를 피해서 경로저장
//		{
//			path_stack.push((*it)->GetEntrance());
//			(*it)->SetConnectExit(true);
//			temp->SetConnectEnter(true);
//		}
//		temp = (*it);
//	}
//	for(it=vec_map.begin();it!=vec_map.end();it++) 
//	{
//		if(PathSearch(temp->GetEntrance(),(*it)->GetExit(),path_stack,ST_MAP,num))//방에 걸린 마스크를 피해서 경로저장
//		{
//			path_stack.push((*it)->GetEntrance());
//			(*it)->SetConnectExit(true);
//			temp->SetConnectEnter(true);
//		}
//		temp = (*it);
//	}
//
//
//	for(int i = 0;i<DG_MAX_X;i++)
//		for(int j = 0;j<DG_MAX_Y;j++)
//			env[num].dgtile[i][j].tile = DG_WALL; //다시 전부 벽으로
//
//
//
//
//
//	for(it=vec_map.begin();it!=vec_map.end();it++) 
//	{//방을 만든다.
//		(*it)->make_map(env[num], false);
//		/*(*it)->make_door(env[num]);*/
//	}
//
//	while(!path_stack.empty())
//	{
//		coord_def path_temp = path_stack.top();
//		env[num].dgtile[path_temp.x][path_temp.y].tile = DG_FLOOR; //저장한 도로를 칠하기
//		path_stack.pop();
//	}	
//	for(it=vec_special_map.begin();it!=vec_special_map.end();it++) 
//	{//방을 만든다.
//		(*it)->make_map(env[num], false);
//	}
//
//	for (it=vec_special_map.begin();it!=vec_special_map.end();it++)
//		delete *it;
//
//	for (it=vec_map.begin();it!=vec_map.end();it++)
//		delete *it;
//
//	for(int i=0;i<6;i++)
//	{
//		while(1)
//		{
//			int x = randA(DG_MAX_X-1),y=randA(DG_MAX_Y-1);
//			if(env[num].dgtile[x][y].tile == DG_FLOOR  && !(env[num].dgtile[x][y].flag & FLAG_NO_MONSTER) )
//			{
//				if(i>2)
//				{
//					env[num].stair_up[i-3].x = x;
//					env[num].stair_up[i-3].y = y;
//					if(num == YOUKAI_MOUNTAIN_LEVEL)
//						env[num].dgtile[x][y].tile = DG_RETURN_STAIR;
//					else
//						env[num].dgtile[x][y].tile = DG_UP_STAIR;
//				}
//				else
//				{
//					env[num].stair_down[i].x = x;
//					env[num].stair_down[i].y = y;
//					env[num].dgtile[x][y].tile = DG_DOWN_STAIR;	
//				}
//				break;
//			}
//		}
//	}
//}
//
//void map_algorithms03(int num)
//{
//	vector<map_dummy*> vec_map;
//	vector<map_dummy*> vec_special_map;
//	vector<int> special_enter;
//	calcul_spe_enter(num,special_enter);
//
//	int prev_x=0;
//	int prev_y=0;
//	int step = 0;
//
//
//
//	for(int i=0;i<40;i++)
//	{
//		int j=0;
//		for(;j<50;j++) //무한반복 제거용
//		{
//			bool success= false;
//			int next_x=0,next_y=0;
//			int r_size_x = rand_int(1,5);
//			int r_size_y = r_size_x;
//			int m_size=10;
//			if(step != 1)
//				next_x = randA(DG_MAX_X-(r_size_x+2)*2-1-m_size*2)+r_size_x+2+m_size;
//			else
//				next_x = prev_x+rand_int(-r_size_x+1,r_size_x-1);
//
//			if(step != -1)
//				next_y = randA(DG_MAX_Y-(r_size_y+2)*2-1-m_size*2)+r_size_y+2+m_size;
//			else
//				next_y = prev_y+rand_int(-r_size_y+1,r_size_y-1);
//
//			coord_def temp_coord(next_x,next_y);		
//			map_dummy* temp = new map_dummy(temp_coord, false,r_size_x,r_size_y,1); //랜덤한 맵더미
//
//			if(step)
//			{
//				if(step == 1)
//				{
//					temp->SetEnter(coord_def(next_x,prev_y>next_y?next_y+r_size_y-1:next_y-r_size_y+1));
//				}
//				else
//				{
//					temp->SetEnter(coord_def(prev_x>next_x?next_x+r_size_x-1:next_x-r_size_x+1,next_y));
//				}
//			}
//
//			
//			vector<map_dummy*>::iterator it;
//			if(vec_map.empty())
//				success = true;
//
//			for (it=vec_map.begin();it!=vec_map.end();it++) 
//			{
//				if(distan_coord(temp->pos,(*it)->pos)<=(temp->size_x+(*it)->size_x+1)*(temp->size_x+(*it)->size_x+1))
//				{
//					success = true;
//					break;
//				}
//			}
//			//for (it=vec_special_map.begin();it!=vec_special_map.end();it++) 
//			//{
//			//	if((*it)->collution(temp_coord,r_size_x,r_size_y) || (*it)->plus_collution(temp_coord,r_size_x,r_size_y)) //맵더미충돌시엔 만들지 않음
//			//	{
//			//		success = false;
//			//		break;
//			//	}
//			//}
//			if(success) //겹치지 않을때 맵더미푸쉬
//			{
//				step = (step!=-1)?-1:1;
//				prev_x = next_x+rand_int(-r_size_x+1,r_size_x-1);
//				prev_y = next_y+rand_int(-r_size_y+1,r_size_y-1);
//				temp->SetExit(coord_def(prev_x,prev_y));
//				vec_map.push_back(temp);
//				break;
//			}
//			else
//			{
//				delete temp; //겹치면 메모리 해제하고 다시 맵더미 생성
//				continue;
//			}
//		}
//		if(j==0)
//		{
//			step = 0;	
//		}
//	}
//
//
//	int rand_dummy = special_enter.size();
//	for(int i=0;i<rand_dummy;i++) //rand_dummy만큼의 맵더미를 생산
//	{	
//		int repeat = 10;
//		int pattern_ = 1;
//		bool special_ = false;
//		if(!special_enter.empty())
//		{
//			special_ = true;
//			repeat = 99999;//특수패턴은 (거의)무한반복시킴
//			pattern_ = special_enter.back();
//			special_enter.pop_back();
//		}
//		for(int j=0;j<repeat;j++) //무한반복 제거용
//		{
//			bool success= false;
//			int r_size_x = rand_int(3,8);
//			int r_size_y = rand_int(3,8);
//			int m_size=20;
//			coord_def temp_coord(randA(DG_MAX_X-(6+2)*2-1-m_size*2)+6+2+m_size,randA(DG_MAX_Y-(6+2)*2-1-m_size*2)+6+2+m_size);		
//			map_dummy* temp = new map_dummy(temp_coord, false,r_size_x,r_size_y,pattern_); //랜덤한 맵더미
//			
//			vector<map_dummy*>::iterator it;
//			for (it=vec_map.begin();it!=vec_map.end();it++) 
//			{
//				if(distan_coord(temp->pos,(*it)->pos)<=(temp->size_x+(*it)->size_x+1)*(temp->size_x+(*it)->size_x+1))
//				{
//					success = true;
//					break;
//				}
//			}
//			for (it=vec_special_map.begin();it!=vec_special_map.end();it++) 
//			{
//				if((*it)->collution(temp_coord,r_size_x,r_size_y) || (*it)->plus_collution(temp_coord,r_size_x,r_size_y)) //맵더미충돌시엔 만들지 않음
//				{
//					success = false;
//					break;
//				}
//			}
//
//
//			if(success) //겹치지 않을때 맵더미푸쉬
//			{
//				vec_special_map.push_back(temp);
//				break;
//			}
//			else
//			{
//				delete temp; //겹치면 메모리 해제하고 다시 맵더미 생성
//				continue;
//			}
//		}
//	}
//
//
//
//
//	vector<map_dummy*>::iterator it;
//	//for(it=vec_special_map.begin();it!=vec_special_map.end();it++)  //방들을 마스크주기
//	//	(*it)->mask(env[num]);
//
//
//	//stack<coord_def> path_stack;
//	//map_dummy* temp = vec_map.back();
//	//
//	//for(it=vec_special_map.begin();it!=vec_special_map.end();it++) 
//	//{
//	//	if(PathSearch(temp->GetEntrance(),(*it)->GetExit(),path_stack,ST_MAP,num))//방에 걸린 마스크를 피해서 경로저장
//	//	{
//	//		path_stack.push((*it)->GetEntrance());
//	//		(*it)->SetConnectExit(true);
//	//		temp->SetConnectEnter(true);
//	//	}
//	//	temp = (*it);
//	//}
//	//for(it=vec_map.begin();it!=vec_map.end();it++) 
//	//{
//	//	if(PathSearch(temp->GetEntrance(),(*it)->GetExit(),path_stack,ST_MAP,num))//방에 걸린 마스크를 피해서 경로저장
//	//	{
//	//		path_stack.push((*it)->GetEntrance());
//	//		(*it)->SetConnectExit(true);
//	//		temp->SetConnectEnter(true);
//	//	}
//	//	temp = (*it);
//	//}
//
//
//	for(int i = 0;i<DG_MAX_X;i++)
//		for(int j = 0;j<DG_MAX_Y;j++)
//			env[num].dgtile[i][j].tile = DG_WALL; //다시 전부 벽으로
//
//
//
//
//
//	for(it=vec_map.begin();it!=vec_map.end();it++) 
//	{//방을 만든다.
//		(*it)->make_map(env[num], false);
//		/*(*it)->make_door(env[num]);*/
//	}
//
//	//while(!path_stack.empty())
//	//{
//	//	coord_def path_temp = path_stack.top();
//	//	env[num].dgtile[path_temp.x][path_temp.y].tile = DG_FLOOR; //저장한 도로를 칠하기
//	//	path_stack.pop();
//	//}	
//	for(it=vec_special_map.begin();it!=vec_special_map.end();it++) 
//	{//방을 만든다.
//		(*it)->make_map(env[num], false);
//	}
//
//	for (it=vec_special_map.begin();it!=vec_special_map.end();it++)
//		delete *it;
//
//	for (it=vec_map.begin();it!=vec_map.end();it++)
//		delete *it;
//
//	for(int i=0;i<6;i++)
//	{
//		while(1)
//		{
//			int x = randA(DG_MAX_X-1),y=randA(DG_MAX_Y-1);
//			if(env[num].dgtile[x][y].tile == DG_FLOOR  && !(env[num].dgtile[x][y].flag & FLAG_NO_MONSTER) )
//			{
//				if(i>2)
//				{
//					env[num].stair_up[i-3].x = x;
//					env[num].stair_up[i-3].y = y;
//					if(num == YOUKAI_MOUNTAIN_LEVEL)
//						env[num].dgtile[x][y].tile = DG_RETURN_STAIR;
//					else
//						env[num].dgtile[x][y].tile = DG_UP_STAIR;
//				}
//				else
//				{
//					env[num].stair_down[i].x = x;
//					env[num].stair_down[i].y = y;
//					if(num != YOUKAI_MOUNTAIN_LAST_LEVEL)
//						env[num].dgtile[x][y].tile = DG_DOWN_STAIR;	
//				}
//				break;
//			}
//		}
//	}
//
//
//	{//임시
//		//while(num == YOUKAI_MOUNTAIN_LEVEL+MAX_YOUKAI_MOUNTAIN_LEVEL)
//		//{
//		//	int x = randA(DG_MAX_X-1),y=randA(DG_MAX_Y-1);
//		//	if(env[num].dgtile[x][y].tile == DG_FLOOR)
//		//	{
//		//		item_infor t;
//		//		env[num].MakeItem(coord_def(x,y),makeitem(ITM_GOAL, 0, &t, 0));
//		//		break;
//		//	}
//		//}
//	}
//}
