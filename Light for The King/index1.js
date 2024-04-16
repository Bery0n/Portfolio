const start    = document.querySelector("#starting")
const game     = document.querySelector("#game")
const palace   = document.querySelector("#palace")
const b_accpet = document.querySelector("#accept")

const i_name = document.querySelector("#name")
const advname = document.querySelector("#advname")

b_accpet.addEventListener("click", clickAccpet)
function clickAccpet() {
    if (i_name.value !== ""){advname.innerText = i_name.value}
    game.classList.remove("hidden")
    maps.classList.remove("hidden")
    start.classList.add("hidden")
}

const maps       = document.querySelector("#maps")
const b_kitchen  = document.querySelector("#kitchen")
const b_lobby    = document.querySelector("#lobby")
const b_dungeons = document.querySelector("#dungeons")

const table    = document.querySelector(".board")
const b_retry = document.querySelector("#retry")
const b_toKing = document.querySelector("#toKing")
const b_run    = document.querySelector("#run")

b_retry.addEventListener("click", clickRetry)
function clickRetry() {
    switch (place) {
        case "kitchen":
            draw(board1)
            break;
        case "lobby":
            draw(board2)
            break;
        default:
            draw(board3)
            break;
    }
    resetStopwatch()
    startStopwatch()
}
b_toKing.addEventListener("click", clickToKing)
function clickToKing() {
    palace.classList.add("hidden")
    maps.classList.remove("hidden")
    game.classList.remove("winGame")
    stopStopwatch()
    resetStopwatch()
}
b_run.addEventListener("click", clickRun)
function clickRun() {
    palace.classList.add("hidden")
    game.classList.add("hidden")
    start.classList.remove("hidden")
    advname.innerText = "Adventure"
    game.classList.remove("winGame")
    stopStopwatch()
    resetStopwatch()
}

let n = 0
let win = 0

let place = ""

let board1 = [
    ['p','p','p','1','p','p','p'],
    ['p','0','p','p','p','2','p'],
    ['p','p','p','p','p','p','p'],
    ['w','p','p','w','p','p','w'],
    ['p','p','p','p','p','p','p'],
    ['p','w','p','p','p','2','p'],
    ['p','p','p','3','p','p','p']]

let board2 =[
    ['p','p','0','p','w','p','p'],
    ['p','p','p','p','p','p','p'],
    ['w','p','w','p','3','p','w'],
    ['p','p','p','1','p','p','p'],
    ['2','p','w','p','w','p','w'],
    ['p','p','p','p','p','p','p'],
    ['p','p','w','p','2','p','p']] 

let board3 = [
    ['p','w','p','p','p','p','p','p','p','p'],
    ['p','p','p','p','p','3','p','2','p','w'],
    ['p','0','w','p','p','p','p','w','p','p'],
    ['p','p','p','p','w','p','p','p','p','p'],
    ['p','1','p','p','w','1','w','p','p','p'],
    ['p','p','p','w','w','w','p','p','3','p'],
    ['p','p','p','p','p','w','p','p','p','p'],
    ['p','p','1','p','p','p','p','0','w','p'],
    ['3','p','w','p','0','p','p','p','p','p'],
    ['p','p','p','p','p','p','p','p','0','p']]

let Map = [[]]
let eMap = [[]]

function handleChoose() {
    maps.classList.add("hidden")
    place = this.getAttribute("id")
    switch (place) {
        case "kitchen":
            draw(board1)
            break;
        case "lobby":
            draw(board2)
            break;
        default:
            draw(board3)
            break;
    }
    palace.classList.remove("hidden")
    startStopwatch()
}

delegate(maps,"click", "a", handleChoose)

//Draw the table
function draw(TheMap) {
    game.classList.remove("winGame")

    table.innerHTML = ""
    Map = TheMap
    let n = Map.length

    for (let i = 0; i < n; i++) {
        let tr = document.createElement("tr")
        
        for (let j = 0; j < n; j++) {
            let td = document.createElement("td")
            td.classList.add("bordered")
            switch (Map[i][j]) {
                case 'p':
                    td.classList.add("pure")
                    break;
                case 'w':
                    td.classList.add("wall")
                    break;
                case 'b':
                    td.classList.add("blight")
                    let bulb_light = document.createElement("img")
                    bulb_light.src = "./img/bulb_light.png"
                    td.appendChild(bulb_light)
                    if (eMap[i][j] === 'be') { td.classList.add("berror") }
                    break;
                case 'l':
                    td.classList.add("light")
                    break;
                case 'n':
                    td.classList.add("npure")
                    break;
                default:
                    td.classList.add("nwall")
                    td.innerText = Map[i][j]
                    if (isWallFull(i,j) == Map[i][j])     {td.classList.add("fullwall")}
                    else if (isWallFull(i,j) > Map[i][j]) {td.classList.add("werror")}
                    else {td.classList.add("wempty")}
                    break;
            }
            tr.appendChild(td)
        }
        table.appendChild(tr)
    }
}
//Draw the solution
function winDraw(theMap) {
    game.classList.add("winGame")
    table.innerHTML = ""
    for (let i = 0; i < n; i++) {
        let tr = document.createElement("tr")
        
        for (let j = 0; j < n; j++) {
            let td = document.createElement("td")
            td.classList.add("bordered")
            switch (Map[i][j]) {
                case 'w':
                    td.classList.add("wall")
                    td.classList.add("fullwall")
                    break;
                case 'b':
                    td.classList.add("blight")
                    let bulb_light = document.createElement("img")
                    bulb_light.src = "./img/bulb_light.png"
                    td.appendChild(bulb_light)
                    break;
                case 'l':
                    td.classList.add("light")
                    break;
                default:
                    td.classList.add("nwall")
                    td.innerText = Map[i][j]
                    td.classList.add("fullwall")
                    break;
            }
            tr.appendChild(td)
        }
        table.appendChild(tr)
    }
}

//Read from the table and write to the Map
function readIntoMaps() {
    n    = Array.from(table.querySelectorAll("tr")).length
    Map  = Array.from(Array(n), () => new Array(n))
    eMap = Array.from(Array(n), () => new Array(n))
    //console.log(Map)
    let columns = Array.from(table.querySelectorAll("tr"))
    // console.log(rows)
    for (let i = 0; i < n; i++) {
        let row = Array.from(columns[i].querySelectorAll("td"))
        // console.log(row)
        for (let j = 0; j < n; j++) {
            // console.log(fieldType(row[j]))
            Map[i][j]  = fieldType(row[j])
            eMap[i][j] = ''
        }
    }
    // console.log(eMap)
}

//Return the type of the fild
function fieldType( field) {
    let type = ""

    if (field.classList.contains("pure"))        {type = 'p'}
    else if (field.classList.contains("wall"))   { type = 'w'}
    else if (field.classList.contains("blight")) { type = 'b'}
    else if (field.classList.contains("light"))  { type = 'l'}
    else if (field.classList.contains("npure"))  { type = 'n'}
    else { type = field.innerText}

    return type
}

//Based on the src and from (where is the source) set the type of Map[i][j] 
function srpeadLight(src, from, i, j) {

    switch (src) {
        //Map[i][j] is a bulb light
        case 'x':
            if (j < n-1) {srpeadLight('b',"left", i, j+1)}
            if (j > 0)   {srpeadLight('b',"right", i, j-1)}
            if (i < n-1) {srpeadLight('b',"top",i+1, j)}
            if (i > 0)   {srpeadLight('b',"bottom", i-1, j)}
            break;
        //the field is nearby bulb light
        case 'b':
            if ( Map[i][j] === 'p' || Map[i][j] === 'l') {
                switch (from) {
                    case "left":
                        Map[i][j] = 'l'
                        if (j<n-1) {srpeadLight('b', "left", i, j+1)}
                        break;
                    case "right":
                        Map[i][j] = 'l'
                        if (j > 0) {srpeadLight('b', "right", i, j-1)}
                        break;
                    case "top":
                        Map[i][j] = 'l'
                        if (i < n-1) {srpeadLight('b', "top", i+1, j)}
                        break;
                    default:
                        Map[i][j] = 'l'
                        if (i > 0) {srpeadLight('b', "bottom", i-1, j)}
                        break;
                }
            } else if (Map[i][j] === 'b') {eMap[i][j] = 'be'}
            break;
        //Map[i][j] is neutral pure
        case 'y':
            Map[i][j] = 'p'
            if (j < n-1) {srpeadLight('n',"left", i, j+1)}
            if (j > 0)   {srpeadLight('n',"right", i, j-1)}
            if (i < n-1) {srpeadLight('n',"top",i+1, j)}
            if (i > 0)   {srpeadLight('n',"bottom", i-1, j)}
            break;
        case 'n':
            if ( Map[i][j] === 'p' || Map[i][j] === 'l') {
                switch (from) {
                    case "left":
                        Map[i][j] = 'p'
                        if (j<n-1) {srpeadLight('n', "left", i, j+1)}
                        break;
                    case "right":
                        Map[i][j] = 'p'
                        if (j > 0) {srpeadLight('n', "right", i, j-1)}
                        break;
                    case "top":
                        Map[i][j] = 'p'
                        if (i < n-1) {srpeadLight('n', "top", i+1, j)}
                        break;
                    default:
                        Map[i][j] = 'p'
                        if (i > 0) {srpeadLight('n', "bottom", i-1, j)}
                        break;
                }
            } else if (Map[i][j] === 'b') {eMap[i][j] = ''}
            break;
        default:
            break;
    }
}
//Start the spreading Special fields: b = bulb light, n = neutral field (deleted bulb light)
function findSpecials() {
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            if(Map[i][j] == 'n') {srpeadLight('y', "zero", i, j)}
        }
    }
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            if (Map[i][j] == 'b') {srpeadLight('x',"zero", i, j)}
        }
    }
}

//return number of the nearby lamps
function isWallFull(i,j) {
    let f = 0
    if (j < n-1) { if (Map[i][j+1] ==='b') {f++} }
    if (j > 0)   { if (Map[i][j-1] ==='b') {f++} }
    if (i < n-1) { if (Map[i+1][j] ==='b') {f++} }
    if (i > 0)   { if (Map[i-1][j] ==='b') {f++} }
    
    return f
    
}

//count mistakes and return (number of them == 0)
function isWin() {
    win = 0
    let trs = Array.from(table.querySelectorAll("tr"))
    if (trs.length == 0) {return false}
    else {
        trs.forEach(tr => {
            let tds = Array.from(tr.querySelectorAll("td"))
            tds.forEach(td => {
                if (td.classList.contains("pure"))        {win++}
                else if (td.classList.contains("wempty")) {win++}
                else if (td.classList.contains("werror")) {win++}
                else if (td.classList.contains("berror")) {win++}
            })
        });
        return (win == 0)
    }
}

function handleTdClick() {
    //Place a bulb light on a pure field
    if (this.classList.contains("pure")) {
        this.classList.replace("pure", "blight")
    }
    //pace bulb light on a lightened field
    else if (this.classList.contains("light")) {
        this.classList.replace("light","blight")
    }
    else if (this.classList.contains("blight")) {
        this.classList.replace("blight","npure")
    }


    readIntoMaps()
    findSpecials()
    draw(Map)
    if (isWin()) {
        winDraw(Map)
        stopStopwatch()
    }
    // console.log(isWin())
}
//DELEGATION in game
delegate(table, "click", "td", handleTdClick)
 
function delegate(parent, type, selector, handler) {
    parent.addEventListener(type, function(event) {
        const targetElement = event.target.closest(selector)
        if (this.contains(targetElement)) {
            handler.call(targetElement, event)
        }
    })
}

//Stopwatch functions 
let hour = 0;
let minute = 0;
let second = 0;
let count = 0;
  
function startStopwatch() {
    timer = true;
    stopWatch();
}
  
function stopStopwatch() {
    timer = false;
}
  
function resetStopwatch() {
    timer = false;
    hour = 0;
    minute = 0;
    second = 0;
    count = 0;
    document.getElementById('hr').innerHTML = "00";
    document.getElementById('min').innerHTML = "00";
    document.getElementById('sec').innerHTML = "00";
    document.getElementById('count').innerHTML = "00";
}
  
function stopWatch() {
    if (timer) {
        count++;
  
        if (count == 100) {
            second++;
            count = 0;
        }
  
        if (second == 60) {
            minute++;
            second = 0;
        }
  
        if (minute == 60) {
            hour++;
            minute = 0;
            second = 0;
        }
  
        let hrString = hour;
        let minString = minute;
        let secString = second;
        let countString = count;
  
        if (hour < 10) {
            hrString = "0" + hrString;
        }
  
        if (minute < 10) {
            minString = "0" + minString;
        }
  
        if (second < 10) {
            secString = "0" + secString;
        }
  
        if (count < 10) {
            countString = "0" + countString;
        }
  
        document.getElementById('hr').innerHTML = hrString;
        document.getElementById('min').innerHTML = minString;
        document.getElementById('sec').innerHTML = secString;
        document.getElementById('count').innerHTML = countString;
        setTimeout(stopWatch, 10);
    }
}