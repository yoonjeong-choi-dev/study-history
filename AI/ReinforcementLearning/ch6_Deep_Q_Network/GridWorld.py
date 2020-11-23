""" Simple GridWorld Environment
1. 84*84*3 grid
    - row, column, (red, green, blue)
    - blue : start grid
    - red : grid to avoid i.e reward=-1
    - green : grid to reach i.e reward=1

2. hero 라는 객체(current position)이 움직인다.
 - hero 가 목표지점에 도착하면 보상은 +1 되고  목표지점은 랜덤하게 바뀐다.
 - hero 가 함정에 빠지면 보상이 -1 되고, 함정의 위치는 랜덤하게 바뀐다.

"""



import numpy as np
import random
import itertools
import scipy.misc
import matplotlib.pyplot as plt



class gameObject:
    def __init__(self, coordinates, size, intensity, channel, reward, name):
        """
        :param coordinates: [x_pos, y_pos]
        :param size: size of the object
        :param intensity:
        :param channel: 2-start/ 1-goal/ 0-fire to avoid
        :param reward: goal-1 / fire-(-1)
        :param name: grid name
        """
        self.x = coordinates[0];
        self.y = coordinates[1];
        self.size = size;
        self.intensity = intensity;
        self.channel = channel;
        self.reward = reward;
        self.name = name;






class gameEnvironment:

    def __init__(self, partial, size, num_goal=4, num_fire=2):
        # size of the grid
        self.sizeX = size;
        self.sizeY = size;

        # action : up/down/right/left
        self.actions = 4;

        # objects : coordinate information for hero(cur_pos), goal, hole(fire)
        self.objects = [];
        self.goals = num_goal;
        self.fires = num_fire;

        # partial : True
        #          => the hero has only partial view
        #          => i.e the agent take partial state
        self.partial = partial;

        self.state = None;

        state = self.reset();
        #plt.imshow(state, interpolation="nearest");


    def reset(self):
        self.objects = [];
        hero = gameObject(self.newPosition(), 1, 1, 2, None, "hero");
        self.objects.append(hero);

        # goal1 = gameObject(self.newPosition(), 1, 1, 1, 1, "goal");
        # self.objects.append(goal1);
        #
        # fire1 = gameObject(self.newPosition(), 1, 1, 0, -1, "fire");
        # self.objects.append(fire1);
        #
        # goal2 = gameObject(self.newPosition(), 1, 1, 1, 1, "goal");
        # self.objects.append(goal2);
        #
        # fire2 = gameObject(self.newPosition(), 1, 1, 0, -1, "fire");
        # self.objects.append(fire2);
        #
        # goal3 = gameObject(self.newPosition(), 1, 1, 1, 1, "goal");
        # self.objects.append(goal3);
        #
        # goal4 = gameObject(self.newPosition(), 1, 1, 1, 1, "goal");
        # self.objects.append(goal4);

        goals = self.goals;
        fires = self.fires;
        while not (goals == 0 and fires == 0):
            if np.random.rand(1) < 0.5 and goals !=0:
                goal = gameObject(self.newPosition(), 1, 1, 1, 1, "goal");
                self.objects.append(goal);
                goals -= 1;
            elif fires != 0:
                fire = gameObject(self.newPosition(), 1, 1, 0, -1, "fire");
                self.objects.append(fire);
                fires -= 1;
            else:
                continue;



        state = self.renderEnv();
        self.state = state;
        return state;

    def move(self, direction):
        # 0 : up / 1 : down / 2 : left / 3 : right
        hero = self.objects[0];
        hero_x = hero.x;
        hero_y = hero.y;

        penalize = 0.0;

        # act with the input direction
        # Think the matrix

        # up : y-coordinate -1
        if direction == 0 and hero.y >= 1:
            hero.y -= 1;
        # down : y-coordinate +1
        if direction == 1 and hero.y <self.sizeY -1:
            hero.y += 1;
        # left : x-coordinate -1
        if direction == 2 and hero.x >= 1:
            hero.x -= 1;
        # right : x-coordinate +1
        if direction == 3 and hero.x < self.sizeX-1:
            hero.x += 1;

        # when the move of the direction is not available
        if hero.x ==hero_x and hero.y == hero_y:
            penalize = 0.0;

        # update the position of the hero
        self.objects[0] = hero;

        return penalize;



    def newPosition(self):
        """ Return a random position without positions which have been already set"""
        itr_pos = [range(self.sizeX), range(self.sizeY)];
        points = [];

        # points[point] : (x_pos, y_pos)
        for point in itertools.product(*itr_pos):
            points.append(point);

        cur_pos = [];

        for objectA in self.objects:
            if(objectA.x, objectA.y) not in cur_pos:
                cur_pos.append((objectA.x, objectA.y));

        for pos in cur_pos:
            points.remove(pos);

        location = np.random.choice(range(len(points)), replace=False);
        return points[location];



    def checkGoal(self):
        others_wrt_hero = [];
        hero = None;

        # update hero / other object
        for obj in self.objects:
            if obj.name == 'hero':
                hero = obj;
            else:
                others_wrt_hero.append(obj);

        is_End = False;

        for other in others_wrt_hero:
            # if hero visit the goals or the fires
            if hero.x == other.x and hero.y == other.y:
                # Remove the cur_pos(hero)
                self.objects.remove(other);

                # reward == 1(goal) => change the goal position
                if other.reward == 1:
                    self.objects.append(gameObject(self.newPosition(), 1, 1, 1, 1, 'goal'));
                # reward == -1(fire) => change the fire position
                else:
                    self.objects.append(gameObject(self.newPosition(), 1, 1, 0, -1, 'fire'));
                # reward
                return other.reward, False;

        # if the hero visit the non-conditioned grid
        if is_End is False:
            return 0.0, False;


    def renderEnv(self):
        # Add boundary i.e add 2 coordinates for each axis(x, y)
        # Set all grids of env as 0 and set the boundary grids as 1
        # grid_with_boundary[y][x] = gird[y-1][x-1]
        grid_with_boundary = np.ones([self.sizeY+2, self.sizeX+2, 3]);
        grid_with_boundary[1:-1, 1:-1, :] = 0;

        hero = None;

        for item in self.objects:
            grid_with_boundary[item.y+1:item.y+1+item.size, item.x+1:item.x+1+item.size, item.channel] = item.intensity;

            if item.name == 'hero':
                hero = item;

        if self.partial is True:
            grid_with_boundary = grid_with_boundary[hero.y:hero.y+3, hero.x:hero.x+3, :];

        r = scipy.misc.imresize(grid_with_boundary[:, :, 0], [84, 84, 1], interp='nearest');
        g = scipy.misc.imresize(grid_with_boundary[:, :, 1], [84, 84, 1], interp='nearest');
        b = scipy.misc.imresize(grid_with_boundary[:, :, 2], [84, 84, 1], interp='nearest');

        grid_with_boundary = np.stack([r, g, b], axis=2);
        return grid_with_boundary;

    def step(self, action):
        penalty = self.move(action);
        reward, is_done = self.checkGoal();
        state = self.renderEnv();

        if reward is None:
            print("is done? : {}".format(is_done));
            print("Reward : {}".format(reward));
            print("Penalty : {}".format(penalty));
            #return state, (reward + penalty), is_done;
            return state, penalty, is_done;
        else:
            return state, (reward + penalty), is_done;


















