using UnityEngine;

public class open : MonoBehaviour
{
    [SerializeField] private GameObject panelToOpen;

    public void HidePanel()
    {
        Debug.Log("Check"); 
        if (panelToOpen != null)
        {
            panelToOpen.SetActive(true);
        }
    }
}
