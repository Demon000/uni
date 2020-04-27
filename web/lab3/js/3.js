(function() {
    const gameContainer = document.querySelector("#game-container");
    const gameStartButton = document.querySelector("#game-start");
    const memoryGame = new MemoryGame({
        element: gameContainer,
        data: [
            1, 2, 3, 4, 5, 6
        ],
       type: MemoryGameType.NUMBERS,
       //  data: [
       //      "assets/images/boianr.jpg",
       //      "assets/images/coroiua.jpg",
       //      "assets/images/gabic.jpg",
       //      "assets/images/istvanc.jpg",
       //      "assets/images/laurad.jpg",
       //      "assets/images/sucium.jpg",
       //  ],
       //  type: MemoryGameType.IMAGES,
        rows: 3,
        cols: 4,
    });
    gameStartButton.addEventListener("click", () => memoryGame.start());
})();
