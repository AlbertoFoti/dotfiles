function setGreeting(greeting: string) {
    const element = document.getElementById('greeting');
    element.innerText = greeting;
}

setGreeting('Hello World!');