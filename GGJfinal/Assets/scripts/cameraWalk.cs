using UnityEngine;
using System.Collections;

public class cameraWalk : MonoBehaviour {

	private GameObject player;

	// Use this for initialization
	void Start () {
		player = GameObject.FindGameObjectWithTag("Director").GetComponent<GameDirector>().player;
	}
	
	// Update is called once per frame
	void Update () {
	

		Camera.main.transform.position = new Vector3(player.transform.position.x, player.transform.position.y, -10f);

	}
}
