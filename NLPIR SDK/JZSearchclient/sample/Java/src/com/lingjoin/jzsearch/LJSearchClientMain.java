package com.lingjoin.jzsearch;

public class LJSearchClientMain {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			String query = "[cmd] listall";
			String ip = "127.0.0.1";
			int port = 98;
			String result = CLibrarySearchClient.Instance.jzsearch_query_client(query,
					0, 200, ip, port);
			System.out.println(result);
		} catch (Exception e) {
			e.printStackTrace();
		}

	}

}
