t = 0
init_pos = 5
time_step = 0.01
q_p_ball = 10

while q_p_ball > 0:

    p_ball = init_pos - (0.5*10*t*t)

    t = t + time_step

    q_p_ball = p_ball

print(t - time_step)
