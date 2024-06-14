document.addEventListener('DOMContentLoaded', function() {
  const generateNameBtn = document.getElementById('generate-name-btn');
  const generateBackgroundBtn = document.getElementById('generate-background-btn');

  generateNameBtn.addEventListener('click', function() {
    generateRandomCharacterName();
  });

  generateBackgroundBtn.addEventListener('click', function() {
    generateRandomCharacterBackground();
  });

  function generateRandomCharacterName() {
    const names = ['Aldric', 'Elysia', 'Thorn', 'Lyra', 'Garrick', 'Bob', 'Alisas']; // list of names
    const randomIndex = Math.floor(Math.random() * names.length);
    const characterName = names[randomIndex];
    document.getElementById('character-name').value = characterName;
  }

  function generateRandomCharacterBackground() {
    const backgrounds = ['Brave and fearless warrior', 'Mysterious sorceress with dark powers', 'Skilled archer with keen eyes', 'Wise and cunning rogue', 'Quick to stumble but fit to rumble barbarian']; // list of backgrounds
    const randomIndex = Math.floor(Math.random() * backgrounds.length);
    const characterBackground = backgrounds[randomIndex];
    document.getElementById('character-background').value = characterBackground;
  }
});
