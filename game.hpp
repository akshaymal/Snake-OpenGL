int obsx[20];//array storing x co-ordinates of obstalces
int obsy[20];//array storing y co-ordinates of obstacles
int count=0;//count checks how many gems were collected
int obsflag=1;//flag to keep or remove obstacles
int special;//checks if the gem is special or not

class fruct{
	public:
		int x, y;//x and y co-ordinate of gem
		
		
			
		void gen() {//generator function for gems
			if(sh%5==0 && sh!=5)
		{
			special=1;
		}
			x = rand() % VM_N;
			y = rand() % VM_M;
			
			for(int i = 0; i < sh; i++)
				if(s[i].x == x && s[i].y == y)
					gen();
			for(int i=0;i<20;i++)
			{
			if(obsx[i]==x && obsy[i]==y)//make sure gem is not positioned on an obstacle
				gen();
			}
		}
		
		
		void draw() {//drawing funtion of gems
			if(special==1)
				glColor3f(1,1,0);
			else
				(1, 0, 0);
			glRecti(x * VM_Scale - 1, y * VM_Scale, (x + 1) * VM_Scale, (y + 1) * VM_Scale + 1);
		}
};



fruct fru;








class game {
	public:
		void over() {
			std::ofstream RO("save.snk");
			
			RO << myMX;
			
			RO.close();
			
			
			exit(0);
		}
		
		
		void drawField() {
			glColor3f(1,1,1);
			glBegin(GL_LINES);//drawing a grid using white lines
				for(int i = 0; i < VM_N; i++) {
					glVertex2i(i * VM_Scale, 0);	glVertex2i(i * VM_Scale, VD_H);
				}
				for(int i = 0; i < VM_M; i++) {
					glVertex2i(0, i * VM_Scale);	glVertex2i(VD_W, i * VM_Scale);
				}
			glEnd();
			for(int i=0;i<20 && obsflag==1 ;i++)//drawing obstacles
			{	
				glColor3f(1,1,1);
				glRecti(obsx[i] * VM_Scale - 1, obsy[i] * VM_Scale, (obsx[i] + 1) * VM_Scale, (obsy[i] + 1) * VM_Scale + 1);
			}
					glEnd();	
			
		}
		
		/*void output()
		{
		  string s = to_string(sh);
		  glColor3f( 1,1, 1 );
		  glRasterPos2f(20,20);
		  for(int i=0;i<s.length();i++)
		  	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,s[i]);
		}*/


		void drawSnake() {//drawing snake
			glColor3f(1, 1, 0);
			glRecti(s[0].x * VM_Scale - 1, s[0].y * VM_Scale, (s[0].x + 1) * VM_Scale, (s[0].y + 1) * VM_Scale + 1);
			
			glColor3f(1, 0, 1);
			for(int i = 1; i < sh; i++)
				glRecti(s[i].x * VM_Scale - 1, s[i].y * VM_Scale, (s[i].x + 1) * VM_Scale, (s[i].y + 1) * VM_Scale + 1);
		}
		
		
		
		void stroke() {//refreshing the grid
			if(count==1 && special==1)
			{
				special=0;
				fru.gen();
				count=0;
			}
			for(int i = sh; i > 0; i--) {
				s[i].x = s[i-1].x;
				s[i].y = s[i-1].y;
			}
			
			if(dir == 1)
				s[0].y += 1;
			if(dir == 2)
				s[0].x += 1;
			if(dir == 3)
				s[0].y -= 1;
			if(dir == 4)
				s[0].x -= 1;
			
			
			if(fru.x == s[0].x && fru.y == s[0].y ) {//checking if gem is eaten
				sh++;
				if (special == 1 && obsflag==1)
				{
					obsflag=0;
					special=0;
				}
				if(special==1 && obsflag==0)
				{
					obsflag=1;
					assign();
					special=0;
				}
				fru.gen();
				if(sh > MX)
					myMX = sh;
				
				if(step > 1)
					step -=0.5;
			}
			
			for(int i=0;i<sh;i++)//circular movement 
			{
				s[i].x=(s[i].x+VM_N)%VM_N;
				s[i].y=(s[i].y+VM_M)%VM_M;
			}

			for(int i=1;i<sh;i++)//if snake crashes with itself
			{
				if(s[0].x==s[i].x && s[0].y==s[i].y)
					over();
			}
			for(int i=0;i<20&& obsflag==1;i++)
			{
				if(obsx[i]==s[0].x && obsy[i]==s[0].y)//if snake crashes with an obstacle
					over();
			}						
			/*if(s[0].x < 0 || s[0].x >= VM_N || s[0].y < 0 || s[0].y >= VM_M)
				over();*/
			
			
			for(int i = 1; i < sh; i++)
				if(s[0].x == s[i].x && s[0].y == s[i].y)
					sh = i+1;
		}

		void assign()//assign random position to obstacles
		{
			for(int i=0;i<20;i++)
			{
				obsx[i]=rand()%VM_M;
				obsy[i]=rand()%VM_N;
			}
		}

		static void keyboard(int key, int a, int b) {//keyboard input
			switch(key) {
				case 101:
					if(dir != 3)
						dir = 1;
				break;
				
				case 102:
					if(dir != 4)
						dir = 2;
				break;
				
				case 103:
					if(dir != 1)
						dir = 3;
				break;
				
				case 100:
					if(dir != 2)
						dir = 4;
				break;
			}
		}
};
