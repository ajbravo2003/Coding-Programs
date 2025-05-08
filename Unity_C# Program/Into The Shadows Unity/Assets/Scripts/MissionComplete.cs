using UnityEngine;
using TMPro; // For TextMeshPro UI
using UnityEngine.SceneManagement;

public class MissionCompleteTrigger : MonoBehaviour
{
    public TextMeshProUGUI missionText; // Reference to the UI text
    public string nextSceneName = "CreditScene";

    private void OnTriggerEnter(Collider other)
    {
        // Check if the player is the one that collided with the trigger
        Debug.Log("Check");
        if (other.CompareTag("Player"))  // Ensure the player has the "Player" tag
        {
            // Show "Mission Complete" text in the UI
            missionText.text = "Mission Complete";
            missionText.enabled = true; // Enable the TextMeshPro UI element

            // Pause the game
            // Time.timeScale = 0f;
            SceneManager.LoadScene(nextSceneName);

            // Optionally, you can trigger any other end-of-game behavior here, like showing a menu
            // For example, you might show a "Play Again" or "Exit" button on the UI
        }
    }
}
