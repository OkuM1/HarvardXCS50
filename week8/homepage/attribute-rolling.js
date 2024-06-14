document.addEventListener('DOMContentLoaded', function() {
    const rollAttributesBtn = document.getElementById('roll-attributes-btn');

    rollAttributesBtn.addEventListener('click', function() {
      const attributes = rollAttributes();
      const attributeSum = Object.values(attributes).reduce((sum, value) => sum + value, 0);
      const titleElement = document.getElementById('attribute-result');

      let title;
      if (attributeSum < 30) {
        title = "Please don't be reckless my weak friend.";
      } else if (attributeSum >= 30 && attributeSum <= 40) {
        title = "You got this.";
      } else if (attributeSum > 40 && attributeSum <= 55) {
        title = "You shall crush your enemies.";
      } else {
        title = "Make sure to return before lunch, mighty hero.";
      }

      titleElement.textContent = title;

      const attributeStatsElement = document.getElementById('attribute-stats');
      attributeStatsElement.innerHTML = '';

      for (let attribute in attributes) {
        const listItem = document.createElement('li');
        listItem.textContent = `${attribute}: ${attributes[attribute]}`;
        attributeStatsElement.appendChild(listItem);
      }
    });

    function rollAttributes() {
      const attributes = {
        strength: rollD20(),
        constitution: rollD20(),
        dexterity: rollD20(),
        intelligence: rollD20(),
        wisdom: rollD20(),
        charisma: rollD20()
      };

      return attributes;
    }

    function rollD20() {
      return Math.floor(Math.random() * 20) + 1; // Generates a random number between 1 and 20
    }
  });
