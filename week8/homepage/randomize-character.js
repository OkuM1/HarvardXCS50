document.addEventListener('DOMContentLoaded', function() {
  const randomizeCharacterBtn = document.getElementById('randomize-character-btn');

  randomizeCharacterBtn.addEventListener('click', function() {
    // Generate random character details
    const randomCharacter = generateRandomCharacter();

    // Set the generated character details in the respective fields
    document.getElementById('character-name').textContent = randomCharacter.name;
    document.getElementById('character-background').textContent = randomCharacter.background;

    // Clear previous equipment and attribute stats
    const equipmentList = document.getElementById('equipment-list');
    const attributeStats = document.getElementById('attribute-stats');
    equipmentList.innerHTML = '';
    attributeStats.innerHTML = '';

    // Display equipment
    for (let slot in randomCharacter.equipment) {
      const item = randomCharacter.equipment[slot];
      const listItem = document.createElement('li');
      listItem.textContent = `${slot}: ${item}`;
      equipmentList.appendChild(listItem);
    }

    // Display attribute stats
    for (let stat in randomCharacter.stats) {
      const value = randomCharacter.stats[stat];
      const listItem = document.createElement('li');
      listItem.textContent = `${stat}: ${value}`;
      attributeStats.appendChild(listItem);
    }

    // Set the generated character description in the input field
    document.getElementById('description-input').value = randomCharacter.description;
  });

  function generateRandomCharacter() {
    const characterName = generateRandomName();
    const characterBackground = generateRandomBackground();
    const equipment = generateRandomEquipment();
    const stats = generateRandomStats();
    const description = generateRandomDescription();

    return {
      name: characterName,
      background: characterBackground,
      equipment: equipment,
      stats: stats,
      description: description
    };
  }

  function generateRandomName() {
    const names = ['Aldric', 'Elysia', 'Thorn', 'Lyra', 'Garrick']; // Replace with your list of names
    const randomIndex = Math.floor(Math.random() * names.length);
    return names[randomIndex];
  }

  function generateRandomBackground() {
    const backgrounds = ['Brave and fearless warrior', 'Mysterious sorceress with dark powers', 'Skilled archer with keen eyes', 'Wise and cunning rogue']; // Replace with your list of backgrounds
    const randomIndex = Math.floor(Math.random() * backgrounds.length);
    return backgrounds[randomIndex];
  }

  function generateRandomEquipment() {
    const equipmentSlots = ['Armor', 'Helm', 'Weapon']; // Replace with your list of equipment slots
    const prefixes = ['Normal', 'Polished', 'Divine', 'Dwarven', 'Draconic']; // Replace with your list of prefixes
    const suffixes = [' of Evil', ' touched by the Blessed Mother', ' of Infinite Wisdom', " of Giant's Strength", ' of Shadowwalker\'s Stride', ' witnessed by the Old One']; // Replace with your list of suffixes
    const equipment = {};

    for (let slot of equipmentSlots) {
      const randomPrefix = prefixes[Math.floor(Math.random() * prefixes.length)];
      const randomSuffix = suffixes[Math.floor(Math.random() * suffixes.length)];
      const randomItem = `${randomPrefix} ${slot}${randomSuffix}`;
      equipment[slot] = randomItem;
    }

    return equipment;
  }

  function generateRandomStats() {
    const stats = {
      strength: getRandomStatValue(),
      constitution: getRandomStatValue(),
      dexterity: getRandomStatValue(),
      intelligence: getRandomStatValue(),
      wisdom: getRandomStatValue(),
      charisma: getRandomStatValue()
    };

    return stats;
  }

  function generateRandomDescription() {
    const descriptions = ['Brave and fearless warrior', 'Mysterious sorceress with dark powers', 'Skilled archer with keen eyes', 'Wise and cunning rogue']; // Replace with your list of descriptions
    const randomIndex = Math.floor(Math.random() * descriptions.length);
    return descriptions[randomIndex];
  }

  function getRandomStatValue() {
    return Math.floor(Math.random() * 21); // Generates a random number between 0 and 20 (inclusive)
  }
});


