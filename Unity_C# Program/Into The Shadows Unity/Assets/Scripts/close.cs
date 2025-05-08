using UnityEngine;

public class buttonVisibles : MonoBehaviour
{
    [SerializeField] private GameObject panelToHide;

    public void HidePanel()
    {
        if (panelToHide != null)
        {
            panelToHide.SetActive(false);
        }
    }
}
