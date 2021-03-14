# Steering Behaviour

## Seek

<img src="https://github.com/Sakyawira/Visual-Novel-Plugin/blob/feature/documentation/ImagesForDocumentation/pasted%20image%200.png?raw=true"/>

1. A vehicle picks a position vector as a target.
2. We generate a desired vector based on our position vector, the target’s 
position vector.
3. A vehicle has a velocity.
4. Our steering vector is the (desired vector – our current velocity).
5. We apply that steering vector to our vehicle.

## Arrive

<img src="https://github.com/Sakyawira/Visual-Novel-Plugin/blob/feature/documentation/ImagesForDocumentation/pasted%20image%200%20(1).png?raw=true"/>

1. Similar to Seek but with one extra process.
2. We normalize the desired vector and then times it with a magnitude that is 
relative to the current distance between the vehicle and the target.
3. As we got closer to the target, we decrease the magnitude of the desired vector 
until it finally becomes zero when it arrived.

## Containment

<img src="https://github.com/Sakyawira/Visual-Novel-Plugin/blob/feature/documentation/ImagesForDocumentation/pasted%20image%200%20(3).png?raw=true" />

1. Set border coordinates.
2. If the vehicle position exceeds those border, reverse its velocity.

## Wander

<img src="https://github.com/Sakyawira/Visual-Novel-Plugin/blob/feature/documentation/ImagesForDocumentation/pasted%20image%200%20(2).png?raw=true"/>

1. The vehicle generates a point within a specified distance and creates a circle 
with a specified radius on it.
2. We get a random point along the circumference of that circle.
3. We seek that point.

## Flock

<img src="https://github.com/Sakyawira/Visual-Novel-Plugin/blob/feature/documentation/ImagesForDocumentation/pasted%20image%200%20(4).png?raw=true"/>

1. Flocking contains three simple steering behaviours.
2. Separation: it calculates the amount of velocity each vehicle needs to stay 
away from other vehicles and set it as your desired vector. This velocity is the 
average of all the desired vector towards a point between each vehicle with 
another. It calculates that point by getting the vector from a vehicle that points 
away from another vehicle and then weighted that vector by dividing it by 
specified magnitude.
3. Cohesion: Get the average position of each vehicle and steer towards that 
position.
4. Alignment: Get the average velocity of all vehicles and steer towards it.

## Leader Following

<img src="https://github.com/Sakyawira/Visual-Novel-Plugin/blob/feature/documentation/ImagesForDocumentation/pasted%20image%200%20(5).png?raw=true"/>

1. Iterate through the vector of vehicles.
2. The first vehicle arrives at a moving target (a mouse, or in my case, a player 
character).
3. The rest of the vehicle arrive at the inverse velocity of the previous vehicle.