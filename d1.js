const raw_data = require('./d1_data')
const data = raw_data.split('\n').map( value => Number(value.trim()) )

// Part 1
let last = data[0], increased = 0;
data.forEach( value => {
    value > last && increased++
    last = value
})
console.log('Part 1: ', increased)

// Part 2
increased = 0
let window_1 = data[0]+data[1]+data[2]
for( let i=3; i<data.length; i++) {
    const window_2 = data[i]+data[i-1]+data[i-2]
    window_2 > window_1 && increased++
    window_1 = window_2
}
console.log('Part 2: ', increased)
