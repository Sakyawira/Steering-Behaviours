# Steering Behaviours

This project showcases my implementation of autonomous agents based on the book 'The Nature of Code' by Daniel Shiffman. There are two things each autonomous agents do: action selection and steering. The autonomous agents (from now we will call them vehicles) will select different sets of actions based on a goal. In this implementation, the user will be able to switch through different goals using their keyboard's number keys. After the vehicles know what their goal is, they will calculate the moves (in this case the vector difference) required to achieve that goal (or for goals that required multiple actions, to achieve each of the actions).

This project is done in C++ and OpenGL. It also features Multi-threading.

### IMPORTANT: Please build the project in x86. Some of the libraries in this project won't work in x64.

## Seek

The goal of the 'Seek' behaviour is to move towards a certain location.

<img src="https://github.com/Sakyawira/Steering-Behaviours/blob/main/gifs/seek.gif?raw=true" width="360" height="360"/>

1. A vehicle picks a position vector as a target.
2. We generate the desired vector based on our position vector, the target’s position vector.
3. A vehicle has a velocity.
4. Our steering vector is the (desired vector – our current velocity).
5. We apply that steering vector to our vehicle.

## Arrive

The goal of the 'Arrive' behaviour is to move towards a certain location. However, we also want it to slow down as it approaches the target.

<img src="https://github.com/Sakyawira/Steering-Behaviours/blob/main/gifs/arrive.gif?raw=true" width="360" height="360"/>

1. Similar to Seek but with one extra process.
2. We normalize the desired vector and then times it with a magnitude that is 
relative to the current distance between the vehicle and the target.
3. As we got closer to the target, we decrease the magnitude of the desired vector 
until it finally becomes zero when it arrived.

## Containment

The goal of the 'Containment' behaviour is to keep the vehicles within a bounding box.

<img src="https://github.com/Sakyawira/Steering-Behaviours/blob/main/gifs/containment.gif?raw=true" width="360" height="360"/>

1. Set border coordinates.
2. If the vehicle position exceeds those border, reverse its velocity.

## Wander

The goal of the 'Wander' behaviour is to let the vehicles move randomly, but still in a natural way.

<img src="https://github.com/Sakyawira/Steering-Behaviours/blob/main/gifs/wander.gif?raw=true" width="360" height="360"/>

1. The vehicle generates a point within a specified distance and creates a circle with a specified radius on it.
2. We get a random point along the circumference of that circle.
3. We seek that point.

## Flock

The goal of the 'Flock' behaviour is to make the vehicles move as a group. We want them to not crash with each other, but we also don't want them to be too far from each other. Lastly, we want them to move towards the same general direction, 

<img src="https://github.com/Sakyawira/Steering-Behaviours/blob/main/gifs/flock.gif?raw=true" width="360" height="360"/>

Flocking contains three simple steering behaviours:
1. Separation: it calculates the amount of velocity each vehicle needs to stay away from other vehicles and set it as your desired vector. This velocity is the 
average of all the desired vector towards a point between each vehicle with 
another. It calculates that point by getting the vector from a vehicle that points 
away from another vehicle and then weighted that vector by dividing it by 
specified magnitude.
2. Cohesion: Get the average position of each vehicle and steer towards that 
position.
3. Alignment: Get the average velocity of all vehicles and steer towards it.

## Leader Following

The goal of 'leader following' is to make all the vehicles follow each other in a line, while the leader of the group moves toward a point.

<img src="https://github.com/Sakyawira/Steering-Behaviours/blob/main/gifs/leaderfollowing.gif?raw=true" width="360" height="360"/>

1. Iterate through the vector of vehicles.
2. The first vehicle arrives at a moving target (a mouse, or in my case, a player character).
3. The rest of the vehicle arrive at the inverse velocity of the previous vehicle.
