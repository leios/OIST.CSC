t = 0
p_ball = 5
vel = 0
time_step = 0.01

while p_ball > 0:

    p_ball = p_ball - (vel*time_step) - (0.5*10*time_step*time_step)

    vel = vel + 10*time_step

    t = t + time_step

print(t - time_step)
